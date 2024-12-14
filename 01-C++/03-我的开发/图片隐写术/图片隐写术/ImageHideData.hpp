#ifndef _IMAGE_HIDE_DATA_HPP_
#define _IMAGE_HIDE_DATA_HPP_
#include<Windows.h>
#include<graphics.h>
#include<stdio.h>
#include<tchar.h>
/*
hide data format:
one pixel include RGB three color part,each one use 8bit
now,use them low 1bit save hide data almost not effect picture display
then,one pixel can save 3*1bit data
one picture size of width*height can save data width*height*3bit data,equals width*height*3/8byte

head define:
IH+Int32
IH:hide flag
Int32:hide data size(byte)

last,max hide data size is:
width*height*3/8-6byte
*/
class ImageHideData{
public:
	ImageHideData(){}
	ImageHideData(TCHAR * filePicturePath){
		loadimage(&m_img, filePicturePath);
	}
	void loadImageFile(TCHAR * filePicturePath){
		loadimage(&m_img, filePicturePath);
	}
	int getPictureHeight(){
		return m_img.getheight();
	}
	int getPictureWidth(){
		return m_img.getwidth();
	}
	int getMaxHideByte(){
		return m_img.getheight()*m_img.getwidth() * 3 / 8 - 6;
	}

	int getHideDataByteSize(){
		HDC hdc = GetImageHDC(&m_img);
		int pi = 0;
		int imgWid = m_img.getwidth();
		int imgHei = m_img.getheight();

		int dataSize = 0;
		pi = readHead(&dataSize, hdc, imgWid);
		if (pi < 0 || dataSize == 0){
			return -1;
		}
		return dataSize;
	}
	//返回值：如果图片能够保存这些数据，执行保存并返回true,否则直接返回false
	bool writeData(unsigned char * data, int dataSize){
		if (dataSize > getMaxHideByte()){
			return false;
		}
		HDC hdc = GetImageHDC(&m_img);
		int imgWid = m_img.getwidth();
		int imgHei = m_img.getheight();

		int pi = writeHead(hdc, dataSize, imgWid);

		unsigned char dbuf[8] = { 0 };
		unsigned char sbuf[3] = { 0 };
		int i = 0;
		//每次取3字节处理3*8=24，也就是3个字节分配给8个像素保存
		while (i <= dataSize){
			memset(dbuf, 0, sizeof(dbuf));
			memset(sbuf, 0, sizeof(sbuf));

			for (int j = 0; j < 3; j++){
				if (i <= dataSize){
					sbuf[j] = data[i];
				}
				i++;
			}

			Src3ToDrt8(sbuf, dbuf);

			for (int j = 0; j < 8; j++){
				int x = pi / imgWid;
				int y = pi%imgWid;
				COLORREF color = GetPixel(hdc, x, y);
				setPixelData(&color, dbuf[j]);
				SetPixelV(hdc, x, y, color);
				pi++;
			}

		}
		return true;
	}
	//返回值，实际读取的数据量，格式不满足，直接返回-1,
	//如果传入参数saveData为空或者maxSaveDataSize为零，返回隐写的数据大小
	int readData(unsigned char * saveData, int maxSaveDataSize){
		HDC hdc = GetImageHDC(&m_img);
		int pi = 0;
		int imgWid = m_img.getwidth();
		int imgHei = m_img.getheight();

		int dataSize = 0;
		pi = readHead(&dataSize, hdc, imgWid);
		if (pi < 0 || dataSize == 0){
			return -1;
		}
		if (saveData == NULL || maxSaveDataSize == 0){
			return dataSize;
		}

		unsigned char dbuf[8] = { 0 };
		unsigned char sbuf[3] = { 0 };
		int i = 0;
		//每次取3字节处理3*8=24，也就是3个字节分配给8个像素保存


		while (i <= dataSize){
			if (i + 3 > maxSaveDataSize){
				break;
			}

			memset(dbuf, 0, sizeof(dbuf));
			memset(sbuf, 0, sizeof(sbuf));

			for (int j = 0; j < 8; j++){
				int x = pi / imgWid;
				int y = pi%imgWid;
				COLORREF color = GetPixel(hdc, x, y);
				dbuf[j] = getPixelData(color);
				pi++;
			}

			Drt8ToSrc3(dbuf, sbuf);


			for (int j = 0; j < 3; j++){
				saveData[i] = sbuf[j];
				i++;

			}


		}
		return i;
	}
	void saveImage(TCHAR * savePictureName){
		saveimage(savePictureName, &m_img);
	}
private:
	int writeHead(HDC hdc, int dataSize, int imgWid){
		unsigned char head[6] = { 'I', 'H', 0, 0, 0, 0 };
		unsigned int tp = dataSize;
		head[2] = (tp >> 24) & 0xff;
		head[3] = (tp >> 16) & 0xff;
		head[4] = (tp >> 8) & 0xff;
		head[5] = (tp)& 0xff;

		unsigned char dbuf[8] = { 0 };
		unsigned char sbuf[3] = { 0 };
		int pi = 0, i = 0;
		for (int k = 0; k < 2; k++){
			memset(dbuf, 0, sizeof(dbuf));
			memset(sbuf, 0, sizeof(sbuf));

			for (int j = 0; j < 3; j++){
				sbuf[j] = head[i];
				i++;
			}

			Src3ToDrt8(sbuf, dbuf);

			for (int j = 0; j < 8; j++){
				int x = pi / imgWid;
				int y = pi%imgWid;
				COLORREF color = GetPixel(hdc, x, y);
				setPixelData(&color, dbuf[j]);
				SetPixelV(hdc, x, y, color);
				pi++;
			}
		}
		return pi;
	}
	int readHead(int * dataSize, HDC hdc, int imgWid){
		unsigned char saveData[6] = { 0 };

		unsigned char dbuf[8] = { 0 };
		unsigned char sbuf[3] = { 0 };
		int pi = 0, i = 0;
		for (int k = 0; k < 2; k++){

			memset(dbuf, 0, sizeof(dbuf));
			memset(sbuf, 0, sizeof(sbuf));

			for (int j = 0; j < 8; j++){
				int x = pi / imgWid;
				int y = pi%imgWid;
				COLORREF color = GetPixel(hdc, x, y);
				dbuf[j] = getPixelData(color);
				pi++;
			}

			Drt8ToSrc3(dbuf, sbuf);


			for (int j = 0; j < 3; j++){
				saveData[i] = sbuf[j];
				i++;

			}
		}
		if (saveData[0] == 'I' && saveData[1] == 'H'){
			int dsize = 0;
			dsize = 0 | (saveData[2] << 24) | (saveData[3] << 16) | (saveData[4] << 8) | saveData[5];
			*dataSize = dsize;
		}
		else{
			*dataSize = 0;
			return -1;
		}
		return pi;
	}

	void Src3ToDrt8(unsigned char * sbuf, unsigned char * dbuf){
		dbuf[0] = (sbuf[0] >> 5) & 0x7;
		dbuf[1] = (sbuf[0] >> 2) & 0x7;
		dbuf[2] = (((sbuf[0]) & 0x3) << 1) | ((sbuf[1] >> 7) & 0x1);
		dbuf[3] = (sbuf[1] >> 4) & 0x7;
		dbuf[4] = (sbuf[1] >> 1) & 0x7;
		dbuf[5] = ((sbuf[1] & 0x1) << 2) | ((sbuf[2] >> 6) & 0x3);
		dbuf[6] = (sbuf[2] >> 3) & 0x7;
		dbuf[7] = sbuf[2] & 0x7;
	}
	void Drt8ToSrc3(unsigned char * dbuf, unsigned char * sbuf){
		sbuf[0] = ((dbuf[0] & 0x7) << 5) | ((dbuf[1] & 0x7) << 2) | ((dbuf[2] >> 1) & 0x3);
		sbuf[1] = ((dbuf[2] & 0x1) << 7) | ((dbuf[3] & 0x7) << 4) | ((dbuf[4] & 0x7) << 1) | ((dbuf[5] >> 2) & 0x1);
		sbuf[2] = ((dbuf[5] & 0x3) << 6) | ((dbuf[6] & 0x7) << 3) | (dbuf[7] & 0x7);
	}
	//返回数据，仅低三位有效，数据对应BGR
	unsigned char getPixelData(COLORREF color){
		unsigned char ret = 0;
		ret = (ret | (getB(color) & 1)) << 1;
		ret = (ret | (getG(color) & 1)) << 1;
		ret = (ret | (getR(color) & 1));
		return ret;
	}
	//设置数据，按低三位设置,BGR
	void setPixelData(COLORREF * color, unsigned char data){
		COLORREF temp = *color;
		unsigned char r = getR(temp);
		unsigned char g = getG(temp);
		unsigned char b = getB(temp);

		unsigned char rd = getRD(data);
		unsigned char gd = getGD(data);
		unsigned char bd = getBD(data);

		unsigned char r1 = ~1;
		r = (r&r1) | rd;
		g = (g&r1) | gd;
		b = (b&r1) | bd;

		*color = RGB(r, g, b);
	}
	unsigned char getBD(unsigned char data){
		return (data >> 2) & 1;
	}
	unsigned char getGD(unsigned char data){
		return (data >> 1) & 1;
	}
	unsigned char getRD(unsigned char data){
		return (data)& 1;
	}
	unsigned char getB(COLORREF c){
		return (c >> 16) & 0xff;
	}
	unsigned char getG(COLORREF c){
		return (c >> 8) & 0xff;
	}
	unsigned char getR(COLORREF c){
		return (c)& 0xff;
	}


	IMAGE m_img;
};

#endif // _IMAGE_HIDE_DATA_HPP_