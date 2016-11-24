/*プログラム変更時の注意事項
変更しない行は変化を与えないように！！
つまり、インデントの変更や空白文字の追加を行わないように！！
他人が見たとき差分がわかりにくくなります
また、プッシュ時のコメントには、変更点を記述するだけではなく、
変更した目的も記述するようにしてください*/

/*camera_ctApp*/
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Cinder.h"
#include "cinder/Capture.h"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "CinderOpenCv.h"
/*BasicApp*/	//water
#include "cinder/app/AppBasic.h"
#include "cinder/TriMesh.h"
#include "cinder/MayaCamUI.h"
#include "cinder/Rand.h"
#include <list>
#include <omp.h>
/*fireApp*/
#include "cinder/Perlin.h"
/*PenkiApp*/
#include "cinder/app/App.h"
#include "cinder/app/RendererDx.h"
//#include "cinder/app/RendererGl.h"
#include "cinder/svg/Svg.h"
#include <list>
#include <random>
/*TurnCubeApp*/
#include "cinder/Camera.h"
#include "cinder/CinderMath.h"
/*Shabon*/
/*window*/
#include "cinder/qtime/QuickTime.h"
#include "cinder/Surface.h"
/*soul lost*/
#include "cinder/ImageIO.h"
#include <math.h>
/*time*/
#include <time.h>

#include<windows.h>

/*audio*/
#include "cinder/audio/Source.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/Voice.h"
#include "cinder/Timeline.h"

#include "Resources.h"

/*drawCountDown*/
#include "cinder/Text.h"
#include "cinder/Utilities.h"
#include "cinder/Font.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace cv;

/*camera_ctApp*/
gl::Texture mTexture;
int camera_X1 = 87;	//カメラに映るパネル左上のx座標
int camera_Y1 = 54;	//y座標
int camera_X2 = 526;	//カメラに映るパネル右下の座標
int camera_Y2 = 470;	//y座標
//int D1x = 420;	//プログラム上での描画部分左上のx座標
//int D1y = 112;	//y座標

/*BasicApp*/
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { (GLfloat)0.6, (GLfloat)0.3, (GLfloat)0.4, (GLfloat)1.0 };
GLfloat mat_diffuse[] = { (GLfloat)0.3, (GLfloat)0.5, (GLfloat)0.8, (GLfloat)1.0 };
GLfloat mat_specular[] = { (GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0 };
GLfloat mat_emission[] = { (GLfloat)0.0, (GLfloat)0.1, (GLfloat)0.3, (GLfloat)0.0 };
GLfloat mat_shininess[] = { 128.0 };
GLfloat no_shininess[] = { 0.0 };
const int BasicApp_N = 106; //100 縦
const int BasicApp_N2 = 102;	//位置合わせ用

/*fireApp*/
const int fireApp_buff = 100;
const float fireApp_a = (const float)0.1;
const float fireApp_XY[2] = { (float)(422), (float)(9) };
const int fireApp_N = (int)(425);
const int fireApp_N2 = (int)(445);

/*TurnCube*/
GLfloat TurnCube_no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat TurnCube_mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat TurnCube_mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat TurnCube_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat TurnCube_mat_emission[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat TurnCube_mat_shininess[] = { 128.0 };
GLfloat TurnCube_no_shininess[] = { 0.0 };

/*Shabon*/
const int Shabon_N = 50;
const int Shabon_L = 60;

/*window*/
GLfloat window_mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 }; //{ 0.6, 0.3, 0.4, 1.0 };
GLfloat window_mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };// { 0.3, 0.5, 0.8, 1.0 };
GLfloat window_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat window_mat_emission[] = { 0.5, 0.5, 0.5, 1.0 };//{ 0, 0, 0, 0 };//{ 0.0, 0.1, 0.3, 0.0 };
GLfloat window_mat_shininess[] = { 128.0 };
GLfloat window_no_shininess[] = { 0.0 };

GLfloat window_index[10][3] = { { 0 - 6, 320, 210 }, { 85 - 6, 320, 27 }, { 168 - 6, 320, 210 }, { 85 - 6, 320, 393 }, { 85 - 6, 320, 210 }, { 85 - 6, 320, 210 }, {43 - 6, 320, 210 }, { 85 - 6, 320, 128 }, { 127 - 6, 320, 210 }, { 85 - 6, 320, 302 } };
GLfloat window_size[2][3] = { { 10, 10, 376 }, { 165, 10, 10 } };
const int movie_size[2][2] = { { 0, 0 }, { 1350, 795 } };

clock_t time_start, time_end;

/*movie*/
GLfloat movie_no_mat[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat movie_mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat movie_mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat movie_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat movie_mat_emission[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat movie_mat_shininess[] = { 128.0 };
GLfloat movie_no_shininess[] = { 0.0 };

//表示場所指定用
int P1 = 640 - 240 + 30;	//271
int P2 = 640 + 225 - 20;	//442
int P3 = 400 - 260 - 10;	//148
int P4 = 400 + 220 - 70;	//301

/*Debug mode: true -> debag mode*/
/*カメラがない場合はtrueにして実行してください*/
bool debag = false;

/*切り替えるスイッチの数*/
const int sw_num = 8;

const char app_name[8][32] = { { "fireApp" }, { "water" }, { "window" }, { "TurnCube" }, { "Shabon" }, { "soul" }, { "PenkiApp" }, { "movie" } }; 
const int program_time = 45;
const double movie_time[9] = {5,6,12,5,5,5,5,32,35}; 

class ProjectionMapping2App : public AppNative {
public:
	void setup();
	void mouseDrag(MouseEvent event);
	void mouseDown(MouseEvent event);
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void resetup(int re_sw);

	double clock_time = 0;
	double ch_time = 0;
	int elapsed_time;
	bool input_flag;

	/*camera_ctApp*/
	int mouseX, mouseY;
	Capture mCap;
	int cnt;
	vector< vector<Point> > contours;
	Mat hsv_image, mask_image;
	Mat erode, dilate;
	double bx, by,x_buff,y_buff;
	double x, y;
	int count,maxC;
	int sw;

	/*BasicApp*/
	list<ci::Vec2f>		mPoints;
	bool DIFFUSE;
	bool AMBIENT;
	bool SPECULAR;
	bool EMISSIVE;
	int wave;
	TriMesh mesh;
	int x1, y1;


	/*fireApp*/
	int fireColor[128][3];
	int fireApp_pos[fireApp_N2 + fireApp_buff][fireApp_N];
	int smokePos[fireApp_N2 + fireApp_buff][fireApp_N];
	int seedpram[fireApp_N2][fireApp_N];
	int						mSeed;
	int						mOctaves;
	float					mTime;
	Perlin					mPerlin;
	float					mFrequency;
	int fireApp_x, fireApp_y;
	int fireApp_circle=50;


	/*PenkiApp*/
	std::random_device rnd;

	/*TurnCube*/
	void reload();
	void fileDrop(FileDropEvent event);

	gl::Texture TurnCube_mTexture;
	Matrix44f TurnCube_mCubeRotation;
	int TurnCube_x, TurnCube_y;
	int TurnCube_f = 0;
	float TurnCube_kaiten = 0;
	float TurnCube_houkou = 0;
	float TurnCube_speed = 0;
	float TurnCube_a = 0;
	//int TurnCube_px = 15;
	bool TurnCube_DIFFUSE;
	bool TurnCube_AMBIENT;
	bool TurnCube_SPECULAR;
	bool TurnCube_EMISSIVE;

	/*Shabon*/
	int Shabon_x, Shabon_y;
	int Shabon_z = 0;
	float Shabon_kyu[Shabon_N][3][3];
	float Shabon_a;

	/*window*/
	void loadMovieFile(const fs::path &moviePath);
	list<ci::Vec2f>		window_mPoints;
	bool window_DIFFUSE;
	bool window_AMBIENT;
	bool window_SPECULAR;
	bool window_EMISSIVE;
	double window_r;
	int window_flag;
	int window_cnt;

	/*movie*/
	int avi;
	Surface movie_mSurface;
	qtime::MovieSurface movie;

	/*soul lost*/
	gl::Texture myImage, myImage2;
	int Frag = 1;
	double soul_Speed = 1.00;
	ci::Vec2f soul_Pos, soul_input, now_xy, xyLeftUp, xyRightDown;
	int soul_PosX, soul_PosY;
	int soul_Count = 0;
	int soul_f = 0;
	double soul_G;
	int i = 0;
	int soul_INorOUT = 0;
	double soul_N;
	void DrawGaussian();
	ci::Vec2f Pos_xy, InputXY;
	double target[2];

	/*drawCountDown*/
	gl::Texture	Count_mTexture;
	int countdown_num;
	int countdown_count;
	void drawCountDown2D();
	void drawCountDown3D();
	void updateCountDown();

	//protected:
	/*BasicApp*/
	float BasicApp_pos[2][BasicApp_N2][BasicApp_N];
	MayaCamUI mMayaCam;
	CameraPersp cam;

	//private:
	/*PenkiApp*/
	struct Waterdrop{
		ci::Vec2d PenkiApp_pos;
		float radius;
		Color color;
		float life;
		bool end;
	};
	list<Waterdrop> waterdrops;
	mt19937 mt;
	normal_distribution<float> norm;

	/*audio*/
	void prepareSettings(Settings *settings){ settings->enableMultiTouch(false); }
	audio::VoiceRef mVoice;
	float BGM_volume;
	float BGM_pan;
};

void ProjectionMapping2App::setup()
{
	/*init*/
	x = y = 0;

	if (!debag){
		/*camera_ctApp*/
		cnt = 0;
		try{
			mCap = Capture(640, 480);
			mCap.start();
		}
		catch (...) {
			console() << "Failed to initialize capture" << std::endl;
		}
	}

	sw = 0;		//0:fireApp, 1:water, 2:window, 3:TurnCube, 4:Shabon, 5:soul, 6:PenkiApp, 7:movie
	avi = 1;	//movie 1:fire_water, 2:water_window, 0:openingMovie.mp4, 3:widow_TurnCube, 4:TurnCube_Shabon, 5~6:load, 7:endroll
	setFullScreen(!isFullScreen());
	resetup(sw);
	elapsed_time = program_time;

	/*water*/
	DIFFUSE = true;
	AMBIENT = true;
	SPECULAR = true;
	EMISSIVE = true;

	/*fire*/
	fireApp_x = fireApp_y = 0;
	for (int i = 0; i < 64; i++){
		fireColor[i][0] = i * 4;
		fireColor[i][1] = 0;
		fireColor[i][2] = 0;
	}
	for (int i = 64; i < 80; i++){
		fireColor[i][0] = 255;
		fireColor[i][1] = (i - 64) * 16;
		fireColor[i][2] = 0;
	}
	for (int i = 80; i < 128; i++){
		fireColor[i][0] = 255;
		fireColor[i][1] = 255;
		fireColor[i][2] = (i - 80) * 5;
	}
	mSeed = clock() & 65535;
	mOctaves = 4;
	mTime = 0.0f;
	mFrequency = 1 * 50 / 200.0f;

	/*TurnCube*/
	TurnCube_DIFFUSE = true;
	TurnCube_AMBIENT = true;
	TurnCube_SPECULAR = true;
	TurnCube_EMISSIVE = true;

	/*penki*/
	mt.seed(rnd());

	/*shabon*/
	for (int i = 0; i < Shabon_N; i++){
		Shabon_kyu[i][0][0] = randFloat((float)P1, (float)P2);
		Shabon_kyu[i][0][1] = randFloat((float)P3, (float)P4);
		Shabon_kyu[i][0][2] = 0;
		//初期速度と色情報
		for (int j = 0; j < 3; j++){
			Shabon_kyu[i][1][j] = 0;
		}
		Shabon_kyu[i][2][0] = randFloat((float)0, (float)1);
		Shabon_kyu[i][2][1] = randFloat((float)0.4, (float)1);
		Shabon_kyu[i][2][2] = randFloat((float)1, (float)1);
	}

	/*window*/
	window_DIFFUSE = true;
	window_AMBIENT = true;
	window_SPECULAR = true;
	window_EMISSIVE = true;

	/*soul*/
	gl::clear(Color(0, 0, 0));
	xyLeftUp[0] = (float)P1;
	xyLeftUp[1] = (float)P3;
	xyRightDown[0] = (float)P2;
	xyRightDown[1] = (float)P4;
	soul_Pos[0]=soul_PosX = (int)xyLeftUp[0];
	soul_Pos[1]=soul_PosY = (int)xyLeftUp[1];

	/*audio*/
	audio::SourceFileRef sourceFile = audio::load(loadAsset("Stream.mp3"));
	mVoice = audio::Voice::create( sourceFile );

	BGM_volume = 1.0;
	BGM_pan = 1.0;
	mVoice->setVolume(BGM_volume);
	mVoice->setPan(BGM_pan);
	//->start();	//drawに移動

	time_start = clock();
	/*countdown*/
	countdown_num=0;
	countdown_count=0;
}

void ProjectionMapping2App::mouseDrag(MouseEvent event)
{
	if (debag){
		x = event.getX()*2;
		y = event.getY()*2.6667;
		console() << x/6 << "," << y/6 << endl;
	}
}

void ProjectionMapping2App::update()
{

	time_end = clock();
	clock_time = time_end - time_start;
	ch_time = clock_time / CLOCKS_PER_SEC;

	if (ch_time >= elapsed_time&&sw!=7){
		sw = 7;
		if(input_flag == false){
			avi = 7;
		}
		resetup(sw);
		mVoice->stop();
		elapsed_time += movie_time[avi];

	}
	else if (ch_time >= elapsed_time && sw == 7){
		if (input_flag == false){
			avi++;
			if (avi == 9){
				avi = 7;
			}
			resetup(sw);
			elapsed_time += movie_time[avi];
		}
		else{
 				sw = avi;
 				elapsed_time += program_time;
 				avi += 1;
 				if (avi == 7){
 					avi = 0;
 				}
 				resetup(sw);
 
 				/*audio*/
 				if (sw != 7) mVoice->start();
				resetup(sw);

				input_flag = false;
		}
	}

	if (!debag){
		/*camera_ctApp*/
		Mat input1(toOcv(mCap.getSurface()));
		cvtColor(input1, hsv_image, CV_BGR2HSV);
		if (sw == 0){
			inRange(hsv_image, Scalar(10, 80, 30), Scalar(32, 255, 255), mask_image);
		}
		//if (sw == 0){
		//	inRange(hsv_image, Scalar(16, 41, 120), Scalar(26, 71, 140), mask_image);	//black(shadow)
		//}
		else if (sw == 1){
			inRange(hsv_image, Scalar(25, 70, 30), Scalar(35, 100, 255), mask_image);
 		}
 		else if (sw == 2){
 			inRange(hsv_image, Scalar(20, 100, 120), Scalar(40, 255, 255), mask_image);
		}
		else{
			inRange(hsv_image, Scalar(20, 80, 120), Scalar(40, 255, 255), mask_image);
		}
		cv::erode(mask_image, erode, cv::Mat(), Point(-1, -1), 2);
		cv::dilate(erode, dilate, cv::Mat(), Point(-1, -1), 4);

		cv::findContours(dilate, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		bx = 0.0; 
		by = 0.0;
		maxC = 10;
#pragma omp parallel
		{
#pragma omp ss
			for (int i = 0; i < contours.size(); i++){
				count = contours.at(i).size();
				x_buff = 0.0; 
				y_buff = 0.0;
				if (count > maxC){
					maxC = count;
					for (int j = 0; j < count; j++){
						x_buff += contours.at(i).at(j).x;
						y_buff += contours.at(i).at(j).y;
					}
					bx = x_buff / count;
					by = y_buff / count;
				}
			}
		}
		if (maxC > 10){
			x = 100 * (bx - camera_X1) / (camera_X2 - camera_X1);
			y = 100 * (by - camera_Y1) / (camera_Y2 - camera_Y1);
 			input_flag = true;
 			if (sw == 7 & (avi == 7 || avi == 8)){
 				sw = 6;
 				elapsed_time += 30;
 				avi = 0;
 				resetup(sw);
 				mVoice->start();
 			}
 		}
 		else{
 			x = -100;
 			y = -100;
 		}
	}

	/*BasicApp:1*/
		if (sw == 1){
			int x1 = (int)(x * BasicApp_N2 / 100);
			int y1 = (int)(y * BasicApp_N / 100);
			if (x1 > 2 && x1 < BasicApp_N2 - 3 && y1 > 2 && y1 < BasicApp_N - 3){

#pragma omp parallel
					{
#pragma omp ss
						for (int i = -2; i <= 2; i++){
							for (int j = -2; j <= 2; j++){
								BasicApp_pos[0][x1 + i][y1 + j] = 50 - BasicApp_N / 5;
							}
						}
					}
			}

		//random wave
		if (wave % 3 == 0){
			int rndX = randInt(5, BasicApp_N2 - 5);
			int rndY = randInt(5, BasicApp_N - 5);
#pragma omp parallel
			{
#pragma omp for
				for (int i = -5; i < 5; i++){
					for (int j = -5; j < 5; j++){
						BasicApp_pos[1][rndX + i][rndY + j] -= (float)(BasicApp_N / 500.0);
					}
				}
			}
			wave = 0;
		}
		wave++;

#pragma omp parallel
		{
#pragma omp for
			for (int i = 1; i < BasicApp_N2 - 1; i++){
				for (int j = 1; j < BasicApp_N - 1; j++){
					BasicApp_pos[1][i][j] = (float)(((BasicApp_pos[0][i - 1][j] + BasicApp_pos[0][i + 1][j] + BasicApp_pos[0][i][j - 1] + BasicApp_pos[0][i][j + 1] - 200) / 4 - (BasicApp_pos[0][i][j] - 50)) + BasicApp_pos[1][i][j] * 0.9);
					if (BasicApp_pos[1][i][j]>20){
						BasicApp_pos[1][i][j] = 20;
					}
					else if (BasicApp_pos[1][i][j] < -20){
						BasicApp_pos[1][i][j] = -20;
					}
				}
			}
		}
#pragma omp parallel
			{
#pragma omp for
				for (int i = 1; i < BasicApp_N2 - 1; i++){
					for (int j = 1; j < BasicApp_N - 1; j++){
						BasicApp_pos[0][i][j] += BasicApp_pos[1][i][j];
					}
				}
			}
	}

	/*fireApp:0*/
		if (sw == 0){
			fireApp_x = (int)(x*fireApp_N / 100);
			fireApp_y = (int)(y*fireApp_N2/ 100);
			if ((fireApp_x > fireApp_circle) && (fireApp_x < fireApp_N - fireApp_circle) && (fireApp_y > 0) && (fireApp_y < fireApp_N2 - fireApp_circle)){
				fireApp_pos[int(fireApp_y)][int(fireApp_x)] = 0;
				console() << "smoke:" <<fireApp_y<<" "<<fireApp_x<< endl;

#pragma omp parallel
				{
#pragma omp for
					for (int i = 0; i < fireApp_circle / 2; i+=2){
						for (int j = 0; j < fireApp_circle - (fireApp_circle / 2 - i)*(fireApp_circle / 2 - i) * 2 / (fireApp_circle / 2); j+=2){
							smokePos[fireApp_y + i + fireApp_buff][fireApp_x + (fireApp_circle / 2 * 2) - fireApp_circle + ((fireApp_circle / 2 - i)*(fireApp_circle / 2 - i) / (fireApp_circle / 2)) + j] = 50;
						}
					}
				}
#pragma omp parallel
				{
#pragma omp for
					for (int i = 0; i < fireApp_circle / 2; i+=2){
						for (int j = 0; j < fireApp_circle - (fireApp_circle / 2 - i)*(fireApp_circle / 2 - i) * 2 / (fireApp_circle / 2); j+=2){
							smokePos[fireApp_y + fireApp_circle - 1 - i + fireApp_buff][fireApp_x + (fireApp_circle / 2 * 2) - fireApp_circle + ((fireApp_circle / 2 - i)*(fireApp_circle / 2 - i) / (fireApp_circle / 2)) + j] = 50;
						}
					}
				}
			}

	//各点(0,0)~(300,300)の火種を配置
#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < fireApp_N2; i++){
					for (int j = 0; j < fireApp_N; j++){
						seedpram[i][j] = (int)(127 * rand() / RAND_MAX) + i / 25;
					}
				}
			}

			//火種が発火する閾値
			int firelevel = 126;	//126

			//火種が発火するか判定
#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < fireApp_N2 - 2; i++){
					for (int j = 1; j < fireApp_N - 1; j++){
						if (firelevel < seedpram[i][j])
							fireApp_pos[i + fireApp_buff][j] = 120;
						else if (seedpram[i][j] < 20)
							fireApp_pos[i + fireApp_buff][j] = (int)(fireApp_pos[i + fireApp_buff][j]*0.3);
					}
				}
			}

			//炎の上昇を計算（周辺の平均を計算）
#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < fireApp_N2 - 2 + fireApp_buff; i++){
					for (int j = 1; j < fireApp_N - 1; j++){
						fireApp_pos[i][j] = (fireApp_pos[i + 1][j] + fireApp_pos[i + 2][j] + fireApp_pos[i][j] + fireApp_pos[i + 1][j - 1] + fireApp_pos[i + 1][j + 1]) / 5;
					}
				}
			}

#pragma omp parallel
			{
#pragma omp for
				for (int i = 0; i < fireApp_N2 - 2 + fireApp_buff; i++){
					for (int j = 2; j < fireApp_N - 2; j++){
						smokePos[i][j] = (smokePos[i + 1][j] + smokePos[i + 2][j] + smokePos[i][j] + smokePos[i + 1][j - 1] + smokePos[i + 1][j + 1] + smokePos[i + 1][j - 2] + smokePos[i + 1][j + 2] + smokePos[i + 2][j - 1] + smokePos[i + 2][j + 1] + smokePos[i + 2][j - 2] + smokePos[i + 2][j + 2] + 7) / 12;
					}
				}
			}
	}

	/*PenkiApp:6*/
	if (sw == 6){
		if (x > 0 && y > 0 && x < 100 && y < 100){
			using normal = std::normal_distribution<float>;
			using uniform = std::uniform_real_distribution<float>;

			for (int i = 0; i < rand() % 10; i++){
				Waterdrop obj;
				obj.life = normal(0.4f, 0.2f)(mt);
				float dx = uniform(-3.0f, 3.0f)(mt);
				float dy = uniform(-3.0f, 3.0f)(mt);
				obj.PenkiApp_pos.x = (P2 - P1)*x / 100 + dx + P1;
				obj.PenkiApp_pos.y = (P4 - P3)*y / 100 + dy + P3;
				obj.radius = normal(10.0f, 7.0f - (abs(dx) + abs(dy)))(mt);
				float r = uniform(0.8f, 1.0f)(mt);
				float g = uniform(0.2f, 0.5f)(mt);
				float b = uniform(0.4f, 0.8f)(mt);
				obj.color = Color(r, g, b);
				obj.end = true;
				waterdrops.push_back(obj);
			}
		}
		std::list<Waterdrop> appends;
		for (auto& obj : waterdrops){
			if (obj.end){
				obj.end = false;

				Waterdrop clone;
				clone.color = obj.color;
				clone.end = true;
				clone.PenkiApp_pos = obj.PenkiApp_pos;
				clone.radius = obj.radius;
				clone.life = obj.life * 0.95f;

				clone.radius *= 0.95f;
				clone.PenkiApp_pos.y += 2;

				appends.push_back(clone);
			}
			obj.life -= 0.01f;
		}
		waterdrops.insert(waterdrops.end(), appends.begin(), appends.end());
		waterdrops.remove_if([](Waterdrop obj) { return obj.life < 0; });
	}

	/*TurnCubeApp:3*/
	if (sw == 3){
		
		TurnCube_x = (int)x;
		TurnCube_y = (int)y;

		if (TurnCube_f == 0){
			if (TurnCube_x > 0 && TurnCube_y > 0 && TurnCube_x < 100 && TurnCube_y < 100){
				TurnCube_f = 2;
			}
		}
		else if (TurnCube_f == 1){
			if (TurnCube_speed < 360*3){
				TurnCube_speed += TurnCube_a;
				TurnCube_a += 0.1;
			}
			else if (TurnCube_speed >= 360 * 3 && TurnCube_speed < 360*6){
				TurnCube_speed += TurnCube_a;
				TurnCube_a -= 0.1;
			}
			else{
				if (TurnCube_x < 0 || TurnCube_y < 0 || TurnCube_x > 100 || TurnCube_y > 100){
					TurnCube_f = 0;
					TurnCube_speed = 0;
					TurnCube_a = 0;
				}
				else{
					TurnCube_speed = 0;
					TurnCube_a = 0;
				}
			}
			//TurnCube_mCubeRotation.rotate(ci::Vec3f(0, TurnCube_houkou, 0), 0);//(float)TurnCube_speed *M_PI/180); //回転
		}
		else if (TurnCube_f == 2){
			if (TurnCube_x > 0 && TurnCube_y > 0 && TurnCube_x < 100/2 && TurnCube_y < 100){
				TurnCube_houkou = 1;
			}
			else if (TurnCube_x > 50 && TurnCube_y > 0 && TurnCube_x < 100  && TurnCube_y < 100){
				TurnCube_houkou = -1;
			}
			TurnCube_f = 1;
		}
	}

	/*Shabon:4*/
	if (sw == 4){
		if (x > 0 && y > 0 && x < 100 && y < 100){
			Shabon_x = (int)((P2 - P1)*x / 100 + P1);
			Shabon_y = (int)((P4 - P3)*y / 100 + P3);
		}

		for (int i = 0; i < Shabon_N; i++){
			Shabon_a = sqrt((Shabon_kyu[i][0][0] - Shabon_x)*(Shabon_kyu[i][0][0] - Shabon_x) + (Shabon_kyu[i][0][1] - Shabon_y)*(Shabon_kyu[i][0][1] - Shabon_y) + (Shabon_kyu[i][0][2] - Shabon_z)*(Shabon_kyu[i][0][2] - Shabon_z));

			if (Shabon_a < Shabon_L){
				Shabon_kyu[i][1][0] = (float)(0.005*(Shabon_kyu[i][0][0] - Shabon_x) / Shabon_a);
				Shabon_kyu[i][1][1] = (float)(0.005*(Shabon_kyu[i][0][1] - Shabon_y) / Shabon_a);
				Shabon_kyu[i][1][2] = (Shabon_kyu[i][0][2] - Shabon_z) / Shabon_a;
			}
			else{
				Shabon_kyu[i][1][0] = 0;
				Shabon_kyu[i][1][1] = 0;
				Shabon_kyu[i][1][2] = 0;
			}
			Shabon_kyu[i][0][0] += Shabon_kyu[i][0][0] * Shabon_kyu[i][1][0];
			Shabon_kyu[i][0][1] += Shabon_kyu[i][0][1] * Shabon_kyu[i][1][1];
			Shabon_kyu[i][0][2] += Shabon_kyu[i][0][2] * Shabon_kyu[i][1][2];
		}
	}

	/*window:2*/
	if (sw == 2){
		if (x > 0 && y > 0 && x < 100 && y < 100){
			window_flag = 1;
		}

		window_r += window_flag * 2;
		if (window_r > 110){
			window_cnt++;
			window_r = 110;
		}
		if (window_cnt > 50){
			window_flag *= -1;
			window_cnt = 0;
		}
		if (window_r < 0)
			window_flag = 0;

		if (movie)
			movie_mSurface = movie.getSurface();
	}
	/*movie*/
	if (sw == 7){
		if (movie)
			movie_mSurface = movie.getSurface();
	}

	/*soul:5*/
	if (sw == 5){	
		soul_input[0] = (int)((P2 - P1)*x / 100 + P1);
		soul_input[1] = (int)((P4 - P3)*y / 100 + P3);

		if (soul_PosY == xyLeftUp[1]&&soul_PosX != xyRightDown[0]){
			soul_PosX += 1;
		}
		else if (soul_PosX == xyRightDown[0] && soul_PosY != xyRightDown[1]){
			soul_PosY += 1;
		}
		else if (soul_PosX != xyLeftUp[0] && soul_PosY == xyRightDown[1]){
 			soul_PosX -= 1;
		}
		else if (soul_PosX == xyLeftUp[0] && soul_PosY != xyLeftUp[1]){
 			soul_PosY -= 1;
		}

		//soul_Pos[0] = (float)soul_PosX;	//現在座標をコピー
 		//soul_Pos[1] = (float)soul_PosY;	//
 
		if (soul_input[0] > xyLeftUp[0] && soul_input[0]<xyRightDown[0] && soul_input[1]>xyLeftUp[1] && soul_input[1] < xyRightDown[1]){
 			target[0] = soul_input[0];
 			target[1] = soul_input[1];
		}
		else{
 			target[0] = soul_PosX;
 			target[1] = soul_PosY;
		}
		soul_N = abs(target[1] - soul_Pos[1]) / abs(target[0] - soul_Pos[0]);
 		if (soul_N <= 1){
 			soul_N = (target[1] - soul_Pos[1]) / (target[0] - soul_Pos[0]);
 			if (abs(target[0] - soul_Pos[0]) > 1){
 				soul_Pos[0] += (int)((target[0] - soul_Pos[0]) / abs(target[0] - soul_Pos[0]));
 				soul_Pos[1] = (int)(soul_Pos[1] + soul_N + 0.5);
 			}
		}
		else{
 			soul_N = (target[0] - soul_Pos[0]) / (target[1] - soul_Pos[1]);
 			if (abs(target[1] - soul_Pos[1]) > 1){
 				soul_Pos[0] = (int)(soul_Pos[0] + soul_N + 0.5);
 				soul_Pos[1] += (int)((target[1] - soul_Pos[1]) / abs(target[1] - soul_Pos[1]));
 			}
		}
	}


	updateCountDown();
}

void ProjectionMapping2App::draw()
{
	//	time_start = clock();


	/*BasicApp*/
	if (sw == 1){
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// gray background
		gl::clear(Colorf(0.0f, 0.0f, 0.0f));
		GLfloat light_position[] = { 500, 0.0f, 100.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// set up the camera 
		gl::pushMatrices();
		gl::setMatrices(mMayaCam.getCamera());

		// enable the depth buffer (after all, we are doing 3D)
		gl::enableDepthRead();
		gl::enableDepthWrite();

		ci::ColorA color(CM_HSV, 0.7f, 0.8f, 1.0f, 1.0f);

		/*lightset*/
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

		// draw the grid on the floor
		//drawGrid();
		gl::color(0.2f, 0.2f, 0.9f, 0.5f);
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < BasicApp_N2 - 1; i++){
				for (int j = 0; j < BasicApp_N - 1; j++){
					mesh.appendVertex(ci::Vec3f((float)i, BasicApp_pos[0][i][j], (float)j));
					mesh.appendColorRgb(Color(0.3f, 0.3f, 1));
					mesh.appendVertex(ci::Vec3f((float)i + 1, BasicApp_pos[0][i + 1][j], (float)j));
					mesh.appendVertex(ci::Vec3f((float)i, BasicApp_pos[0][i][j + 1], (float)(j + 1)));
					mesh.appendVertex(ci::Vec3f((float)i + 1, BasicApp_pos[0][i + 1][j + 1], (float)(j + 1)));
					int vIdx0 = mesh.getNumVertices() - 4;
					int vIdx1 = mesh.getNumVertices() - 3;
					int vIdx2 = mesh.getNumVertices() - 2;
					int vIdx3 = mesh.getNumVertices() - 1;
					ci::Vec3f norm = (ci::Vec3f((float)(i + 1), BasicApp_pos[0][i + 1][j], (float)j) - ci::Vec3f((float)i, BasicApp_pos[0][i][j], (float)j)).cross(ci::Vec3f((float)(i + 1), BasicApp_pos[0][i + 1][j], (float)j) - ci::Vec3f((float)i, BasicApp_pos[0][i][j + 1], (float)(j + 1))).normalized();
					mesh.appendNormal(norm);
					mesh.appendTriangle(vIdx0, vIdx1, vIdx2);
					mesh.appendTriangle(vIdx3, vIdx1, vIdx2);
					gl::draw(mesh);
					mesh.clear();
				}
			}
		}
		gl::popMatrices();

	}

	/*fireApp:0*/
	else if (sw == 0){
		// clear out the window with black
		gl::clear(Color(0, 0, 0));

		/*light off*/
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//炎を描写
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < fireApp_N2 + fireApp_buff; i += 2){
				for (int j = 0; j < fireApp_N; j += 2){
					gl::color(fireColor[fireApp_pos[i][j]][0] * (1 - fireApp_a) + smokePos[i][j] * fireApp_a, fireColor[fireApp_pos[i][j]][1] * (1 - fireApp_a) + smokePos[i][j] * fireApp_a, fireColor[fireApp_pos[i][j]][2] * (1 - fireApp_a) + smokePos[i][j] * fireApp_a);
					gl::drawSolidEllipse(ci::Vec2d(fireApp_XY[0] + j, fireApp_XY[1] + i), 1.0, 1.0);
				}
			}
		}
		if (elapsed_time-ch_time <= 10){
			drawCountDown2D();
		}
	}

	/*PenkiApp:6*/
	else if (sw == 6){
		gl::clear(Color::black());

		/*light off*/
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (auto& obj : waterdrops){
			gl::color(obj.color.r, obj.color.g, obj.color.b, obj.life * 0.25f);
			gl::drawSolidCircle(obj.PenkiApp_pos, obj.radius);
		}
	}

	/*TurnCube:3*/
	else if (sw == 3){
		reload();

		// clear out the window with black
		gl::clear(Color(0, 0, 0));
		if (!TurnCube_mTexture)
			return;

		/*light on*/
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND);

		// enable the depth buffer (after all, we are doing 3D)
		gl::enableDepthRead();
		gl::enableDepthWrite();

		/*light set*/
		ci::ColorA color(CM_HSV, 0.7f, 0.8f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

		glMaterialfv(GL_FRONT, GL_AMBIENT, TurnCube_mat_ambient);

		glMaterialfv(GL_FRONT, GL_SPECULAR, TurnCube_mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, TurnCube_mat_shininess);

		glMaterialfv(GL_FRONT, GL_EMISSION, TurnCube_mat_emission);

		TurnCube_mTexture.bind();
		glPushMatrix();
		glRotated(TurnCube_speed, 0, TurnCube_houkou, 0);
		gl::multModelView(TurnCube_mCubeRotation);

		gl::drawCube(ci::Vec3f(0, 0, 0), ci::Vec3f((float)(228 * 0.454), (float)(230 * 0.454), 0.05f));
		glPopMatrix();
	}

	/*Shabon:4*/
	else if (sw == 4){
		// clear out the window with black
		gl::clear(Color(0, 0, 0));

		/*light off*/
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < Shabon_N; i++){
			if (Shabon_kyu[i][0][0] >= P1 && Shabon_kyu[i][0][0] <= P2 && Shabon_kyu[i][0][1] >= P3 && Shabon_kyu[i][0][1] <= P4){
				gl::color(Color(CM_HSV, Shabon_kyu[i][2][0], Shabon_kyu[i][2][1], Shabon_kyu[i][2][2]));
				//gl::color(Shabon_kyu[i][2][0], Shabon_kyu[i][2][1], Shabon_kyu[i][2][2]);
				gl::drawSolidCircle(ci::Vec2f(Shabon_kyu[i][0][0], Shabon_kyu[i][0][1]), 8, -1);
			}
			else{
				//座標
				Shabon_kyu[i][0][0] = randFloat((float)P1, (float)P2);
				Shabon_kyu[i][0][1] = randFloat((float)P3, (float)P4);

				//色
				Shabon_kyu[i][2][0] = randFloat((float)0, (float)1);
				Shabon_kyu[i][2][1] = randFloat((float)0.4, (float)1);
			}
		}
	}

	/*window:2*/
	else if (sw == 2){
		/*light on*/
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// gray background
		gl::clear(Colorf(0, 0, 0));
		GLfloat light_position[] = { 500, 0.0f, 100.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// set up the camera 
		gl::pushMatrices();
		gl::setMatrices(mMayaCam.getCamera());

		// enable the depth buffer (after all, we are doing 3D)
		gl::enableDepthRead();
		gl::enableDepthWrite();

		/*light set*/
		ci::ColorA color(CM_HSV, 0.7f, 0.8f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

		glMaterialfv(GL_FRONT, GL_AMBIENT, window_mat_ambient);

		glMaterialfv(GL_FRONT, GL_SPECULAR, window_mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, window_mat_shininess);

		glMaterialfv(GL_FRONT, GL_EMISSION, window_mat_emission);

		Rectf bounds((float)416, (float)42, (float)1097, (float)745); //movie size
		gl::enableAlphaBlending(true);

		if ((!movie) || (!movie_mSurface))
			return;

		// We are using OpenGL to draw the frames here, so we'll make a texture out of the surface
		glPushMatrix();
		glTranslated(-270, 10, -200);
		glRotated(90, 1, 0, 0);
		gl::draw(gl::Texture(movie_mSurface), bounds);
		glPopMatrix();
		gl::color(109 / 256.0f, 60 / 256.0f, 50 / 256.0f, 0.5f);

#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < 10; i++){
				glPushMatrix();
				glTranslated(313, 320, 0);
				glRotated(-window_r, 0, 0, 1);
				glTranslated(5, -320, 0);
				if (i < 6)
					gl::drawCube(ci::Vec3f(window_index[i]), ci::Vec3f(window_size[i % 2][0] + 5, window_size[i % 2][1] + 2, window_size[i % 2][2] + 5));
				else gl::drawCube(ci::Vec3f(window_index[i]), ci::Vec3f(window_size[i % 2]));

				glPopMatrix();
			}
		}

#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < 10; i++){
				glPushMatrix();
				glTranslated(658 + 5, 320, 0);
				glRotated(window_r, 0, 0, 1);
				glTranslated(0 - 5, -320, 0);
				if (i < 6)
					gl::drawCube(ci::Vec3f( - window_index[i][0], window_index[i][1], window_index[i][2]), ci::Vec3f(window_size[i % 2][0] + 5, window_size[i % 2][1] + 2, window_size[i % 2][2] + 5));
				gl::drawCube(ci::Vec3f( - window_index[i][0], window_index[i][1], window_index[i][2]), ci::Vec3f(window_size[i % 2]));
				glPopMatrix();
			}
		}
	}

	/*movie:7*/
	else if (sw == 7){
		/*light on*/
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// gray background
		gl::clear(Colorf(0, 0, 0));
		GLfloat light_position[] = { 500, 0.0f, 100.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// set up the camera 
		gl::pushMatrices();
		gl::setMatrices(mMayaCam.getCamera());

		// enable the depth buffer (after all, we are doing 3D)
		gl::enableDepthRead();
		gl::enableDepthWrite();

		/*light set*/
		ci::ColorA color(CM_HSV, 0.7f, 0.8f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

		glMaterialfv(GL_FRONT, GL_AMBIENT, movie_mat_ambient);

		glMaterialfv(GL_FRONT, GL_SPECULAR, movie_mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, movie_mat_shininess);

		glMaterialfv(GL_FRONT, GL_EMISSION, movie_mat_emission);

		Rectf bounds((float)movie_size[0][0], (float)movie_size[0][1], (float)movie_size[1][0], (float)movie_size[1][1]); //movie size
		gl::enableAlphaBlending(true);

		if ((!movie) || (!movie_mSurface)){
			console() << "err" << endl;
			sleep(1000);
			return;
		}

		// We are using OpenGL to draw the frames here, so we'll make a texture out of the surface
		glPushMatrix();
		glTranslated(-270, 10, -200);
		glRotated(90, 1, 0, 0);
		gl::draw(gl::Texture(movie_mSurface), bounds);
		glPopMatrix();
	}

	/*soul:5*/
	else if (sw == 5){
		gl::clear(Color(0, 0, 0));
		DrawGaussian();
	}
		
	if (sw==0||(sw>=4&&sw<=6)){
 		gl::color(0.0f, 0.0f, 255.0f, 1.0f);
 #pragma omp parallel
		{
 #pragma omp for
 			for (int i = 0; i < contours.size(); i++){
 				count = contours.at(i).size();
 				for (int j = 0; j < count; j++){
 					//InputXY[0] = (P2 - P1)*contours.at(i).at(j).x / 100 + P1;
 					//InputXY[1] = (P4 - P3)*contours.at(i).at(j).y / 100 + P3;
 					InputXY[0] = 1280 * contours.at(i).at(j).x / 640;
 					InputXY[1] = 720 * contours.at(i).at(j).y / 480;
 					gl::drawSolidCircle(InputXY, 1);
 				}
			}
		}
		gl::drawSolidCircle(ci::Vec2f((P2 - P1)*x / 100 + P1, (P4 - P3)*y / 100 + P3), 5);
	}
}

void ProjectionMapping2App::reload()
{
	// now tell our Camera that the window aspect ratio has changed
	cam.setPerspective(60, getWindowAspectRatio(), 1, 1000);

	// and in turn, let OpenGL know we have a new camera
	gl::setMatrices(cam);
}

void ProjectionMapping2App::fileDrop(FileDropEvent event)
{
	try {
		TurnCube_mTexture = gl::Texture(loadImage(event.getFile(0)));
	}
	catch (...) {
		console() << "unable to load the texture file!" << std::endl;
	};
}

void ProjectionMapping2App::loadMovieFile(const fs::path &moviePath)
{
	try {
		movie = qtime::MovieSurface(moviePath);

		console() << "Dimensions:" << movie.getWidth() << " x " << movie.getHeight() << std::endl;
		console() << "Duration:  " << movie.getDuration() << " seconds" << std::endl;
		console() << "Frames:    " << movie.getNumFrames() << std::endl;
		console() << "Framerate: " << movie.getFramerate() << std::endl;
		console() << "Alpha channel: " << movie.hasAlpha() << std::endl;
		console() << "Has audio: " << movie.hasAudio() << " Has visuals: " << movie.hasVisuals() << std::endl;
		movie.setLoop(true, true);
		movie.seekToStart();
		movie.play();
	}
	catch (...) {
		console() << "Unable to load the movie." << std::endl;
	}
}

void ProjectionMapping2App::DrawGaussian(){

	Color color[5] = { { 255, 255, 255 }, { 200, 200, 200 }, { 150, 150, 150 }, { 100, 100, 100 }, { 20, 20, 20 } };

	ci::Vec2f soul_Pos_xy;
	double soul_D = 0;

	for (int i = -3; i <= 3; i++){
		for (int j = -3; j <= 3; j++){
			soul_D = sqrt((i*i) + (j*j));

			if (soul_D < sqrt(13)){
				soul_D = ceil(soul_D);
				soul_Pos_xy[0] = soul_Pos[0] + i; 
				soul_Pos_xy[1] = soul_Pos[1] + j;
				gl::color(color[(int)soul_D]);
				gl::drawSolidCircle(soul_Pos_xy, 1.5);
			}
		}
	}
	//console() << soul_Pos_xy << endl;
 	//gl::drawSolidCircle(soul_input, 10);
 	//gl::drawSolidCircle(xyLeftUp, 10);
 	//gl::drawSolidCircle(xyRightDown, 10);
 	//gl::drawSolidCircle(ci::Vec2f(soul_PosX,soul_PosY), 10);
}

void ProjectionMapping2App::resetup(int re_sw){
	/*BasicApp*/
	if (re_sw == 1){
		//set up the camera
		cam.setEyePoint(ci::Vec3f(BasicApp_N2 / 2, 200, BasicApp_N / 2+5));
		cam.setCenterOfInterestPoint(ci::Vec3f(BasicApp_N2 / 2, 0.0f, BasicApp_N / 2+5));
		cam.setPerspective(60.0f, getWindowAspectRatio(), 1.0f, 200.0f);
		mMayaCam.setCurrentCam(cam);

		//init
		for (int j = 0; j < BasicApp_N2; j++){
			for (int k = 0; k < BasicApp_N; k++){
				BasicApp_pos[0][j][k] = 50;
			}
		}
		for (int j = 0; j < BasicApp_N2; j++){
			for (int k = 0; k < BasicApp_N; k++){
				BasicApp_pos[1][j][k] = 0;
			}
		}
	}

	/*fireApp:0*/
	else if (re_sw == 0){
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < fireApp_N2 + fireApp_buff; i++){
				for (int j = 0; j < fireApp_N; j++){
					fireApp_pos[i][j] = 0;
					smokePos[i][j] = 0;
				}
			}
		}
		setFullScreen(!isFullScreen());
		setFullScreen(!isFullScreen());
	}

	/*TurnCubeApp:3*/
	else if (re_sw == 3){
		//画像読み込み
		//fs::path path = getOpenFilePath("movie_snap.png", ImageIo::getLoadExtensions());
		TurnCube_mTexture = gl::Texture(loadImage(loadAsset("movie_snap.png")));

		//視点設定
		cam.setEyePoint(ci::Vec3f(85.5 - 85, -47.5 + 43, 150));
		cam.setCenterOfInterestPoint(ci::Vec3f(85.5 - 85, -47.5 + 43, 0));
		cam.setPerspective(60.0f, getWindowAspectRatio(), 1.0f, 200.0f);
		mMayaCam.setCurrentCam(cam);

		TurnCube_mCubeRotation.setToIdentity();

		glEnable(GL_TEXTURE_2D);
		gl::enableDepthRead();
		gl::enableDepthWrite();
	}

	/*Shabon:4*/
	else if (re_sw == 4){
		//setWindowSize(1000, 800);
		//座標の設定
		setFullScreen(!isFullScreen());
		setFullScreen(!isFullScreen());
	}

	/*window:2*/
	else if (re_sw == 2){
		cam.setEyePoint(ci::Vec3f(320 + 170, 700, 240 - 10));
		cam.setCenterOfInterestPoint(ci::Vec3f(320 + 170, 0, 240 - 10));
		cam.setPerspective(80.0f, getWindowAspectRatio(), 1.0f, 700.0f);
		mMayaCam.setCurrentCam(cam);

		fs::path a_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\MeditationVideo.mp4");
		if (!a_moviePath.empty())
			loadMovieFile(a_moviePath);

		window_r = 0;
		window_flag = 0;
		window_cnt = 0;
	}

	/*movie*/
	else if (re_sw == 7){
		//CameraPersp cam;
		cam.setEyePoint(ci::Vec3f(320 + 170, 700, 240 - 10));
		cam.setCenterOfInterestPoint(ci::Vec3f(320 + 170, 0, 240 -10));
		cam.setPerspective(80.0f, getWindowAspectRatio(), 1.0f, 700.0f);
		mMayaCam.setCurrentCam(cam);

		if (avi == 1){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\fire_water2.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 2){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\water_window.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 8){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\openingMovie.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 3){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\window_TurnCube.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 4){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\TurnCube_Shabon.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 5){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\load.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 6){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\load.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 7){
			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\endroll.mp4");
			if (!avi_moviePath.empty())
				loadMovieFile(avi_moviePath);
		}
		else if (avi == 0){
 			fs::path avi_moviePath("C:\\cinder_0.8.6_vc2013\\projects\\ProjectionMapping\\resources\\load.mp4");
 			if (!avi_moviePath.empty())
 				loadMovieFile(avi_moviePath);
 		}
	}

	/*soul:5*/
	else if (re_sw == 5){
		soul_Pos[0] = soul_PosX = (int)xyLeftUp[0];
 		soul_Pos[1] = soul_PosY = (int)xyLeftUp[1];
 		setFullScreen(!isFullScreen());
 		setFullScreen(!isFullScreen());
 	}
 
 	/*Penki:6*/
 	else if (re_sw == 6){
 		setFullScreen(!isFullScreen());
 		setFullScreen(!isFullScreen());
	}

	console() << app_name[re_sw] << endl;
	//time_start = clock();
}
void ProjectionMapping2App::keyDown(KeyEvent event)
{

	if (event.getChar() == 'f' || event.getChar() == 'F'){
		setFullScreen(!isFullScreen());
	}
	else if (event.getChar() == 'w'){
		window_flag = 1;
		TurnCube_f = 1;
		TurnCube_houkou = -1;
	}
	else if (event.getChar() == 'i'){
 		input_flag = true;
 		if (sw == 7 & (avi == 7 || avi == 8)){
 			sw = 6;
 			elapsed_time += 30;
 			avi = 0;
			resetup(sw);
		}
	}
	else if (event.getChar() >= '0' && event.getChar() <= '6'){
 		sw = event.getChar() - 48;		//0:fireApp, 1:water, 2:window, 3:TurnCube, 4:Shabon, 5:soul, 6:PenkiApp, 7:movie
 		resetup(sw);
 		avi = sw;
 	}
}

void ProjectionMapping2App::mouseDown(MouseEvent event){
	x = event.getX() * 2;
	y = event.getY()*2.6667;
	console() << x << "," << y << endl;
}

void ProjectionMapping2App::drawCountDown2D(){
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	gl::setMatricesWindow(getWindowSize());

	gl::enableAlphaBlending(false);

	gl::color(Color::white());
	gl::draw(Count_mTexture, ci::Vec2f(1000, 600));
}
void ProjectionMapping2App::updateCountDown(){
	TextLayout layout;
	layout.clear(ColorA(0.2f, 0.2f, 0.2f, 0.2f));
	layout.setFont(Font("Arial", 24));
	layout.setColor(Color(1, 1, 1));
	layout.addLine(std::string(to_string(countdown_num)));
	Surface8u rendered = layout.render(true, false);
	Count_mTexture = gl::Texture(rendered);
	countdown_num = elapsed_time - ch_time;
}
void ProjectionMapping2App::drawCountDown3D(){
	gl::setMatricesWindow(getWindowSize());

	gl::enableAlphaBlending(false);

	gl::color(Color::white());
	//gl::draw(Count_mTexture, ci::Vec3f(1000, 600, 1), ci::Vec3f(1000, 600, 1));
}

CINDER_APP_NATIVE(ProjectionMapping2App, RendererGl)