
// IDCardFdvDlg.h : 头文件
//

#pragma once

#include "CvvImage.h"
#include "MsgDlg.h"
#include "OperationDlg.h"
#include "AttentionDlg.h"
#include "InfoDlg.h"
#include "AdvHtmlView.h"
#include "ImgUploadMgt.h"
#include "al.h"
#include "alut.h"
#ifdef NDEBUG
#include "AiFdrWrap.h"
#else
#include <opencv2/objdetect/objdetect.hpp>
#endif
#include <fstream>

#define FDVDLG_DEFAULT_CLEAR_TIME	20

// debug define
#define DEBUG_LOG_FILE	0
#define DEBUG_LIVECHECK_OUTPUT	0

// CIDCardFdvDlg 对话框
class CIDCardFdvDlg : public CDialogEx
{
// 构造
public:
	CIDCardFdvDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CIDCardFdvDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IDCARDFDV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	std::string m_strModulePath;

	std::string m_macId;

	// data loading
	CWinThread* m_thDataLoading;
	bool m_bStopLoading;
	bool m_bDataReady;
	CEvent m_eDataloadingEnd;

	//config data
	std::string m_cfgCameraVid;
	std::string m_cfgCameraPid;
	std::string m_cfgCameraHideVid;
	std::string m_cfgCameraHidePid;
	std::string m_cfgAppId;
	std::string m_cfgApiKey;
	std::string m_cfgSecretKey;
	std::string m_cfgUrl;
	std::string m_cfgUploadUrl;
	std::string m_cfgUploadLoc;
	std::string m_cfgAdvUrl;
	std::string m_cfgTimeOut;
	std::string m_cfgAttStrMain;
	std::string m_cfgRegisteredNo;

	// idcard detect thread
	bool m_bIdcardDetectRun;
	CWinThread* m_thIdcardDetect;
	CEvent m_eIdcardDetectEnd;
	CEvent m_eIdcardDetectResume;
	IplImage* m_iplImgHelpImg;

	// face detect thread
	bool m_bFaceDetectRun;
	CWinThread* m_thFaceDetect;
	CEvent m_eFaceDetectEnd;
	CEvent m_eCaptureForDetect;
	CEvent m_eFaceDetectResume;
	bool m_bCmdDetect;
	std::vector<cv::Rect> m_faces;
	IplImage* m_iplImgCameraImg;
	IplImage* m_iplImgCameraImgHide;

	// camera preview
	//int camdevid;
	bool m_bCameraRun;
	CWinThread* m_thCamera;
	CEvent m_eCameraEnd;
	CEvent m_eCameraResume;	// 手动事件
	int m_iMainDevIdx;
	int m_iHideDevIdx;
	cv::VideoCapture m_vcapMain;
	cv::VideoCapture m_vcapHide;
	bool m_bFlip;
	int m_iPreviewX;
	IplImage* m_iplImgDisplay;
	IplImage* m_iplImgTemp;
	bool m_bDrawScan;
	cv::Mat m_MatScan;
	cv::Mat m_MatScanBorder;
	int m_iPreviewWidth;
	int m_iPreviewHeight;
	bool m_bMainFrameSuccess;	// 用于帧读取错误的重启
	bool m_bHideFrameSuccess;

	// fdv
	CWinThread* m_thFdv;
	bool m_bFdvRun;
	bool m_bCmdFdvStop;
	CEvent m_eFdvEnd;
#ifdef NDEBUG
	fdr_model_wrap* m_pfrmwrap;
#else
	cv::CascadeClassifier faceCascade;
#endif
	std::string m_photoFaceFeat;
	std::vector < std::string> m_frameFaceFeats;

	// images upload thread
	bool m_bImgUploadRun;
	bool m_bImgUploadPause;
	CWinThread* m_thImgUpload;
	CEvent m_eImgUploadEnd;
	CEvent m_eImgUploadResume;
	CImgUploadMgt* m_imgUploadMgt;
	IplImage* m_iplImgUploadCopyFrame;
	IplImage* m_iplImgUploadCopyFrameHide;
	IplImage* m_iplImgUploadCopyPhoto;


	// capture
	IplImage* m_CaptureImage;
	IplImage* m_CaptureImageHide;
	std::string m_sCaptureBase64;
	bool m_bFaceGot;
	bool m_bIsAliveSample;
	IplImage* m_iplImgTestPhoto;	//test
	IplImage* m_iplImgTestImage;	//test
	IplImage* m_iplImgTestImage2;	//test

	bool m_bMainWinClose;

	// idcard
	char m_IDCardId[256];
	char m_IDCardIssuedate[256];
	char m_IDCardPhoto[102400];
	IplImage* m_iplImgPhoto;
	bool m_bIDCardReadOK;
	bool m_bIDCardNoChange;
	CEvent m_eGetIDCardFeat;	// 手动事件

	// msg dialog
	CMsgDlg* m_pMsgDlg;
	int		m_iAniStep;

	// opration panel
	COperationDlg* m_pOperationDlg;

	// attention dialog
	CAttentionDlg* m_pAttentionDlg;

	// info panel
	CInfoDlg* m_pInfoDlg;
	HBITMAP m_hBIconCamera;	// test
	bool	m_bDrawResultIconRight;
	bool	m_bDrawResultIconWrong;
	cv::Mat m_ResultIconRight;
	cv::Mat m_ResultIconWrong;
	double m_dThreshold;
	

	// wav
	bool m_bsndReady;
	ALuint m_sndRightBuffer;
	ALuint m_sndRightSource;
	ALuint m_sndWrongBuffer;
	ALuint m_sndWrongSource;

	// adv
	bool		 m_bShowAdv;
	CAdvHtmlView m_HtmlView;

	// debug
#if DEBUG_LOG_FILE
	std::ofstream m_logfile;
#endif
public:
	void checkAndOpenAllCamera();
	void closeAllCamera();
	void showPreview(IplImage* img, int dX/*display X*/);
	void drawHelpImage(IplImage* img);
	void drawScanRect(cv::Mat frame);
	void drawResultIcon(cv::Mat frame, cv::Mat icon);

	void startDataLoadingThread();
	void stopDataLoadingThread();
	void startIdcardDetectThread();
	void stopIdcardDetectThread();
	void startCameraThread();
	void stopCameraThread();
	void startFaceDetectThread();
	void stopFaceDetectThread();
	bool startFdvThread(std::string feat, bool live);
	void waitFdvThreadStopped();
	void startImgUploadThread();
	void stopImgUploadThread();
	void setClearTimer(float sec = 3.0);
	void stopClearTimer();

	void afterIDCardReadOK();
	bool idcardPreRead();
	
	void getIDCardMatPhoto(cv::Mat &matphoto);
	void getIDCardFeat(cv::Mat &matphoto);

	virtual BOOL DestroyWindow();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// WM_CLOSEFDV
	afx_msg LRESULT OnUpgradeClose(WPARAM wParam, LPARAM lParam);
};
