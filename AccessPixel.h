#pragma once
#include <memory.h>
#include "RGBBYTE.h"


template<typename T>
class AccessPixel // 다양한 자료형의 image 
{
protected:
	int     width;  // 영상의 가로 크기 (픽셀 단위)
	int     height; // 영상의 세로 크기 (픽셀 단위)
	T** pixels; // 픽셀 데이터

public:
	// 생성자와 소멸자
	AccessPixel();
	AccessPixel(int w, int h);
	AccessPixel(const AccessPixel<T>& img);
	~AccessPixel();

	// 이미지 생성과 소멸
	void    CreateImage(int w, int h);
	void    DestroyImage();

	// 픽셀 값 접근
	T* GetPixels()   const {
		if (pixels) return pixels[0];
		else return NULL;
	}// 1차원 픽셀 접근  
	T** GetPixels2D() const { return pixels; } // 2차원 픽셀값 접근  

	// 대입 연산자 재정의
	AccessPixel<T>& operator=(const AccessPixel<T>& img); //operator 접근   

	// 픽셀 값 설정
	template<typename U> void Convert(const AccessPixel<U>& img, bool use_limit = false);

	// 영상 정보 반환
	int     GetWidth()    const { return width; } // 폭 전달 
	int     GetHeight()   const { return height; } // 높이 전달  
	int     GetSize()     const { return width * height; } // 넓이 전달 픽셀 개수랑 같은건가? 
	bool    IsValid()     const { return (pixels != NULL); } //픽셀 값이 있는가  ?  
};

template<typename T>
AccessPixel<T>::AccessPixel()
	:width(0), height(0), pixels(NULL)  // 픽셀 값이 없을 때 
{
}

template<typename T>
AccessPixel<T>::AccessPixel(int w, int h)
	: width(w), height(h), pixels(NULL)
{
	pixels = new T * [sizeof(T*) * height]; // 픽셀의 세로 줄 
	pixels[0] = new T[sizeof(T) * width * height]; // 2d 이미지 픽셀 값 저장 

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width; 

	memset(pixels[0], 0, sizeof(T) * width * height); // 픽셀 값 초기화
}

template<class T>
AccessPixel<T>::AccessPixel(const AccessPixel<T>& img) //픽셀 값에 대한 복사 생성자 
	: width(img.width), height(img.height), pixels(NULL)
{
	if (img.IsValid()) {
		pixels = new T * [sizeof(T*) * height];
		pixels[0] = new T[sizeof(T) * width * height];

		for (int i = 1; i < height; i++)
			pixels[i] = pixels[i - 1] + width;

		memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height); // 픽셀 값 복사
	}
}

template<typename T>
AccessPixel<T>::~AccessPixel() //소멸자 
{
	if (pixels != NULL) {
		delete[] pixels[0]; // 메모리 해제 
		delete[] pixels;
	}
}

template<typename T>
void AccessPixel<T>::CreateImage(int w, int h)
{
	DestroyImage();// 초기화 

	width = w;
	height = h; // 높이와 폭을 얻는다. 

	pixels = new T * [sizeof(T*) * height]; // 높이에 대한 크기를 할당 ? 
	pixels[0] = new T[sizeof(T) * width * height]; // 넓이에 대한 크기를 할당 

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width; //픽셀 전체  행렬? 

	memset(pixels[0], 0, sizeof(T) * width * height); // 픽셀 값 초기화
}

template<typename T>
void AccessPixel<T>::DestroyImage() // 픽셀 값 초기화 
{
	if (pixels != NULL) {
		delete[] pixels[0];
		delete[] pixels;
		pixels = NULL;
	}

	width = height = 0;
}

template<typename T>
AccessPixel<T>& AccessPixel<T>::operator=(const AccessPixel<T>& img)
{
	if (this == &img)
		return *this;

	CreateImage(img.width, img.height); // 이미지 픽셀값을 해당 주소에  더블 포인터로 저장 한다. 
	memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height); // 픽셀값 초기화 

	return *this;
}

template<typename T> template<typename U>
void AccessPixel<T>::Convert(const AccessPixel<U>& img, bool use_limit)
{
	CreateImage(img.GetWidth(), img.GetHeight()); // 이미지의 높이와 폭을 얻는다. 

	int size = GetSize(); //높이 * 폭 
	T* p1 = GetPixels(); // 1차원 픽셀 값 얻기 
	U* p2 = img.GetPixels(); // 이미지의 픽셀값 얻기 

	if (use_limit)
		for (int i = 0; i < size; i++) 
			p1[i] = static_cast<T>(limit(p2[i])); // ??? 
	else
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(p2[i]);
}

// 다양한 자료형에 대한 GetPixel 정의

typedef AccessPixel<BYTE>    ByteImage;
typedef AccessPixel<int>     IntImage;
typedef AccessPixel<float>   FloatImage;
typedef AccessPixel<double>  DoubleImage;
typedef AccessPixel<RGBBYTE> RgbImage;

template<typename T>
inline T limit(const T& value)
{
	return ((value > 255) ? 255 : ((value < 0) ? 0 : value)); // 픽셀 값 0< value < 255 
}