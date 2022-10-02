//#pragma once
//
//#define MAX_OBJECT			250
//#define MAX_WIN_WIDTH		640
//#define MAX_WIN_HEIGHT		480
//
//enum ObjectID
//{
//		eFlag01=1,
//		eFlag02,
//		eFlag03,
//		eFlag04,
//		eFlag05,
//		eFlag06,
//		eFlag07,
//		eFlag08,
//		eFlag09,
//		eFlag10,
//		eFlag11,
//		eFlag12,
//		eFlag13,
//		eFlag14,
//		eFlag15,
//		eFlag16,
//		eFlag17,
//		eFlag18,
//		eFlag19,
//		eFlag20,
//		eFlag21,
//		eFlag22,
//		eTIME,
//		eRankPANEL_MAIN,
//		eRanking,
//		eSAMPLEBUTTON,
//		eSAMPLEBUTTON2,
//		eVip_MAIN,
//		eVip_TITLE,
//		eVip_FRAME,
//		eVip_FOOTER,
//		eVip_DIV,
//		eVip_CLOSE,
//		eVip_BRONZE,
//		eVip_SILVER,
//		eVip_GOLD,
//		eVip_PLATINUM,
//		eVip_STATUS,
//		eRanking_MAIN,
//		eRanking_CLOSE,
//		eLogo,
//		eEventTimePANEL_MAIN,
//		eEventTime_MAIN,
//		eEventTime_CLOSE,
//		eMenu,
//		eMenuBG,
//		eMenu_MAIN,
//		eMenu_TITLE,
//		eMenu_FRAME,
//		eMenu_FOOTER,
//		eMenu_DIV,
//		eMenu_CLOSE,
//		eMenu_OPT1,
//		eMenu_OPT2,
//		eMenu_OPT3,
//		eMenu_OPT4,
//		eMenu_OPT20,
//		eCommand_MAIN,
//		eCommand_TITLE,
//		eCommand_FRAME,
//		eCommand_FOOTER,
//		eCommand_DIV,
//		eCommand_CLOSE,
//};
//
//struct InterfaceObject
//{
//	DWORD	ModelID;
//	float	Width;
//	float	Height;
//	float	X;
//	float	Y;
//	float	MaxX;
//	float	MaxY;
//	DWORD	EventTick;
//	bool	OnClick;
//	bool	OnShow;
//	BYTE	Attribute;
//};
//
//class Interface
//{
//public:
//	//Interface();
//
//
//	void		Load();
//	static void	LoadImages();
//	static void	Work(int unk);
//
//	void		BindObject(short ObjectID, DWORD ModelID, float Width, float Height, float X, float Y);
//	void		DrawGUI(short ObjectID, float PosX, float PosY);
//	void		DrawTimeUI();
//	int			DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...);
//	void		DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
//	void		ResetDrawIMG(short ObjectID);
//	int			DrawMessage(int Mode, LPCSTR Text, ...);
//
//	bool		CheckWindow(int WindowID);
//	int			CloseWindow(int WindowID);
//	int			OpenWindow(int WindowID);
//
//	bool		IsWorkZone(short ObjectID);
//	float		GetResizeX(short ObjectID);
//	int			DrawToolTip(int X, int Y, LPCSTR Text, ...);
//	float		DrawRepeatGUI(short MonsterID, float X, float Y, int Count);
//	void		DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color);
//	void		DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
//
//	//Vip Window
//	void		OpenVipWindow() { this->Data[eVip_MAIN].OnShow = true; pSetCursorFocus = true; };
//	void		CloseVipWindow() { this->Data[eVip_MAIN].OnShow = false; pSetCursorFocus = false; };
//	bool		CheckVipWindow() { return this->Data[eVip_MAIN].OnShow; };
//	void		DrawVipWindow();
//	bool		EventVipWindow_Main(DWORD Event);
//	bool		EventVipWindow_Close(DWORD Event);
//	bool		EventVipWindow_Bronze(DWORD Event);
//	bool		EventVipWindow_Silver(DWORD Event);
//	bool		EventVipWindow_Gold(DWORD Event);
//
//	//Menu
//	void		DrawMenu();
//	bool		EventDrawMenu_Open(DWORD Event);
//	void		OpenMenuWindow() { this->Data[eMenu_MAIN].OnShow = true; pSetCursorFocus = true; };
//	void		CloseMenuWindow() { this->Data[eMenu_MAIN].OnShow = false; pSetCursorFocus = false; };
//	bool		CheckMenuWindow() { return this->Data[eMenu_MAIN].OnShow; };
//	void		DrawMenuOpen();
//	bool		EventDrawMenu_Close(DWORD Event);
//	bool		EventDrawMenu_Op1(DWORD Event);
//	bool		EventDrawMenu_Op2(DWORD Event);
//	bool		EventDrawMenu_Op3(DWORD Event);
//	bool		EventDrawMenu_Op4(DWORD Event);
//	bool		EventDrawMenu_Op20(DWORD Event);
//
//	void		DrawLogo();
//	void		CloseCustomWindow();
//
//	InterfaceObject Data[MAX_OBJECT];
//	
//private:
//	
//};
//extern Interface gInterface;
