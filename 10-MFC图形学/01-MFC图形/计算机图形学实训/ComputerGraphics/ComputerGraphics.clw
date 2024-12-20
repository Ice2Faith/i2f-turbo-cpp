; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=DlgGeoModCreateSetting
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ComputerGraphics.h"
LastPage=0

ClassCount=15
Class1=CComputerGraphicsApp
Class2=CComputerGraphicsDoc
Class3=CComputerGraphicsView
Class4=CMainFrame

ResourceCount=12
Resource1=IDR_MAINFRAME
Resource2=IDD_DLG_GVARY
Class5=CAboutDlg
Class6=DlgColorSetting
Resource3=IDD_DLG_METERIAL
Class7=DlgSizeSetting
Resource4=IDD_DLG_LIGHT
Class8=DlgInputBox
Resource5=IDD_ABOUTBOX
Class9=DlgGraphVarySetting
Resource6=IDD_DLG_GEOMODCREATE
Class10=DlgMaterialSetting
Resource7=IDD_DLG_CARTONSETTING
Class11=DlgLightSetting
Resource8=IDD_DLG_INPUTBOX
Class12=DlgGeoModCreateSetting
Resource9=IDD_DLG_SIZE
Class13=DlgOperationTips
Resource10=IDD_DLG_COLOR
Class14=DlgCartonSetting
Resource11=IDD_DLG_OPERATIONTIPS
Class15=DlgBaseOperationHelp
Resource12=IDD_DLG_BASEOPE

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_GEOMOD_BALLEX




[CLS:CAboutDlg]
Type=0
HeaderFile=ComputerGraphics.cpp
ImplementationFile=ComputerGraphics.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_PEN_COLOR
Command2=ID_PEN_SIZE
Command3=ID_BRUSH_COLOR
Command4=ID_DRAW_NULL
Command5=ID_DRAW_POINT
Command6=ID_DRAW_LINE
Command7=ID_DRAW_CONLINE
Command8=ID_DRAW_CIRCLE
Command9=ID_DRAW_ELIPESE
Command10=ID_DRAW_RECTANGLE
Command11=ID_DRAW_ROUNDRECT
Command12=ID_DRAW_ARC
Command13=ID_DRAW_POLYGON
Command14=ID_DRAW_POLYLINE
Command15=ID_DRAW_BEZIERLINE
Command16=ID_DRAW_GON
Command17=ID_DRAW_CLEANER
Command18=ID_TMFILE_OPEN
Command19=ID_TMFILE_SAVE
Command20=ID_GEOMOD_TETR
Command21=ID_GEOMOD_HEX
Command22=ID_GEOMOD_OCT
Command23=ID_GEOMOD_DODEC
Command24=ID_GEOMOD_ICOS
Command25=ID_GEOMOD_BALL
Command26=ID_GEOMOD_CYLINDER
Command27=ID_GEOMOD_CONE
Command28=ID_GEOMOD_TORUS
Command29=ID_GEOMOD_BALLEX
Command30=ID_TRANGLELIZED
Command31=ID_LINEMODE_BEZIER
Command32=ID_LINEMOD_EDIT
Command33=ID_LINEMOD_BEZIERYSPIN
Command34=ID_LINEMOD_BEZIERXSPIN
Command35=ID_SCANDIS_DDALINE
Command36=ID_SCANDIS_ANTIALIASLINE
Command37=ID_SCAN_SEEDFILL
Command38=ID_SCAN_TRANGLEFILL
Command39=ID_GRAPH_VARY
Command40=ID_PROJ_ORTHOGONAL
Command41=ID_PROJ_MAINVIEW
Command42=ID_PROJ_SIDEVIEW
Command43=ID_PROJ_TOPVIEW
Command44=ID_PROJ_OBLIQUE
Command45=ID_PROJ_WORDTOSCREEN
Command46=ID_PROJ_ONEPOINT
Command47=ID_PROJ_TWOPOINT
Command48=ID_PROJ_THREEPOINT
Command49=ID_PROJ_DEEPSCREEN
Command50=ID_MODHIDE_BACKREMOVE
Command51=ID_MODHIDE_DEEPBUFF
Command52=ID_MODHIDE_NONE
Command53=ID_MODLIGHT_FLAT
Command54=ID_MODLIGHT_MATERIAEX
Command55=ID_MODLIGHT_LIGHT
Command56=ID_MODLIGHT_NONE
Command57=ID_DISMOD_POINTCLOUD
Command58=ID_DISMOD_LINEAR
Command59=ID_DISMOD_FLAT
Command60=ID_DISMOD_NONE
Command61=ID_DISMOD_CLEANPAINTER
Command62=ID_SHOW_ORGLINE
Command63=ID_HIDE_ORGLINE
Command64=ID_CARTON_SETTING
Command65=ID_APP_ABOUT
Command66=ID_OPERATION_TIPS
Command67=ID_OPERATION_BASEOPE
CommandCount=67

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DLG_COLOR]
Type=1
Class=DlgColorSetting
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SLIDER_RED,msctls_trackbar32,1342242840
Control4=IDC_SLIDER_GREEN,msctls_trackbar32,1342242840
Control5=IDC_SLIDER_BLUE,msctls_trackbar32,1342242840
Control6=IDC_STATIC_RED,static,1342308352
Control7=IDC_STATIC_GREEN,static,1342308352
Control8=IDC_STATIC_BLUE,static,1342308352

[CLS:DlgColorSetting]
Type=0
HeaderFile=DlgColorSetting.h
ImplementationFile=DlgColorSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgColorSetting
VirtualFilter=dWC

[DLG:IDD_DLG_SIZE]
Type=1
Class=DlgSizeSetting
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SLIDER_SIZE,msctls_trackbar32,1342242840
Control4=IDC_STATIC_SIZE,static,1342308352

[CLS:DlgSizeSetting]
Type=0
HeaderFile=DlgSizeSetting.h
ImplementationFile=DlgSizeSetting.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SLIDER_SIZE

[DLG:IDD_DLG_INPUTBOX]
Type=1
Class=DlgInputBox
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_INPUT,edit,1350631552
Control4=IDC_STATIC_TIPS,static,1342308352

[CLS:DlgInputBox]
Type=0
HeaderFile=DlgInputBox.h
ImplementationFile=DlgInputBox.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgInputBox

[DLG:IDD_DLG_GVARY]
Type=1
Class=DlgGraphVarySetting
ControlCount=65
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_PROJANGLE,button,1342177287
Control4=IDC_STATIC_PROJAANGLE,static,1342308352
Control5=IDC_EDIT_PROJAANGLE,edit,1350631552
Control6=IDC_STATIC_PROJBANGLE,static,1342308352
Control7=IDC_EDIT_PROJBANGLE,edit,1350631552
Control8=IDC_STATIC_VIEWR,static,1342308352
Control9=IDC_EDIT_VIEWR,edit,1350631552
Control10=IDC_STATIC_VIEWD,static,1342308352
Control11=IDC_EDIT_VIEWD,edit,1350631552
Control12=IDC_STATIC_VIEW,button,1342177287
Control13=IDC_STATIC_VIEWNEAR,static,1342308352
Control14=IDC_EDIT_VIEWRNEAR,edit,1350631552
Control15=IDC_STATIC_VIEWDFAR,static,1342308352
Control16=IDC_EDIT_VIEWDFAR,edit,1350631552
Control17=IDC_STATIC_FNFLAT,button,1342177287
Control18=IDC_STATIC_GMOVEX,static,1342308352
Control19=IDC_EDIT_GMOVEX,edit,1350631552
Control20=IDC_STATIC_GMOVEY,static,1342308352
Control21=IDC_EDIT_GMOVEY,edit,1350631552
Control22=IDC_STATIC_GMOVE,button,1342177287
Control23=IDC_STATIC_GMOVEZ,static,1342308352
Control24=IDC_EDIT_GMOVEZ,edit,1350631552
Control25=IDC_STATIC_GSCALEX,static,1342308352
Control26=IDC_EDIT_GSCALEX,edit,1350631552
Control27=IDC_STATIC_GSCALEY,static,1342308352
Control28=IDC_EDIT_GSCALEY,edit,1350631552
Control29=IDC_STATIC_GSCALE,button,1342177287
Control30=IDC_STATIC_GSCALEZ,static,1342308352
Control31=IDC_EDIT_GSCALEZ,edit,1350631552
Control32=IDC_STATIC_GSPINX,static,1342308352
Control33=IDC_EDIT_GSPINX,edit,1350631552
Control34=IDC_STATIC_GSPINY,static,1342308352
Control35=IDC_EDIT_GSPINY,edit,1350631552
Control36=IDC_STATIC_GSPIN,button,1342177287
Control37=IDC_STATIC_GSPINZ,static,1342308352
Control38=IDC_EDIT_GSPINZ,edit,1350631552
Control39=IDC_CHECK_GREFLACTX,button,1342242819
Control40=IDC_CHECK_GREFLACTY,button,1342242819
Control41=IDC_CHECK_GREFLACTZ,button,1342242819
Control42=IDC_STATIC_GREFLACE,button,1342177287
Control43=IDC_CHECK_GFLATREFXOY,button,1342242819
Control44=IDC_CHECK_GFLATREFYOZ,button,1342242819
Control45=IDC_CHECK_GFLATREFXOZ,button,1342242819
Control46=IDC_STATIC_GFLATREF,button,1342177287
Control47=IDC_STATIC_GMISCUT,button,1342177287
Control48=IDC_STATIC_GMISCUTXGZ,static,1342308352
Control49=IDC_STATIC_GMISCUTXDY,static,1342308352
Control50=IDC_EDIT_GMISCUTXGZ,edit,1350631552
Control51=IDC_EDIT_GMISCUTXDY,edit,1350631552
Control52=IDC_STATIC_GMISCUTYHZ,static,1342308352
Control53=IDC_STATIC_GMISCUTYBX,static,1342308352
Control54=IDC_EDIT_GMISCUTYHZ,edit,1350631552
Control55=IDC_EDIT_GMISCUTYBX,edit,1350631552
Control56=IDC_STATIC_GMISCUTZFY,static,1342308352
Control57=IDC_STATIC_GMISCUTZCX,static,1342308352
Control58=IDC_EDIT_GMISCUTZFY,edit,1350631552
Control59=IDC_EDIT_GMISCUTZCX,edit,1350631552
Control60=IDC_CHECK_MOVE,button,1342242819
Control61=IDC_CHECK_SPIN,button,1342242819
Control62=IDC_CHECK_SCALE,button,1342242819
Control63=IDC_CHECK_FALTREF,button,1342242819
Control64=IDC_CHECK_REFLACT,button,1342242819
Control65=IDC_CHECK_MISCUT,button,1342242819

[CLS:DlgGraphVarySetting]
Type=0
HeaderFile=DlgGraphVarySetting.h
ImplementationFile=DlgGraphVarySetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_FALTREF
VirtualFilter=dWC

[DLG:IDD_DLG_METERIAL]
Type=1
Class=DlgMaterialSetting
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_GOLD,button,1342242819
Control4=IDC_CHECK_SIVER,button,1342242819
Control5=IDC_CHECK_REDSTONE,button,1342242819
Control6=IDC_CHECK_GREENSTONE,button,1342242819

[CLS:DlgMaterialSetting]
Type=0
HeaderFile=DlgMaterialSetting.h
ImplementationFile=DlgMaterialSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO_MATE_GOLD
VirtualFilter=dWC

[DLG:IDD_DLG_LIGHT]
Type=1
Class=DlgLightSetting
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_GOLD,button,1342242819
Control4=IDC_CHECK_SIVIR,button,1342242819
Control5=IDC_CHECK_REDSTONE,button,1342242819
Control6=IDC_CHECK_GREENSTONE,button,1342242819
Control7=IDC_STATIC_GCOLOR,button,1342177287
Control8=IDC_STATIC_GPOINT,button,1342177287
Control9=IDC_STATIC_PX,static,1342308352
Control10=IDC_EDIT_PX,edit,1350631552
Control11=IDC_STATIC_PY,static,1342308352
Control12=IDC_EDIT_PY,edit,1350631552
Control13=IDC_STATIC_PZ,static,1342308352
Control14=IDC_EDIT_PZ,edit,1350631552
Control15=IDC_STATIC_GSUBFACTOR,button,1342177287
Control16=IDC_STATIC_CZERO,static,1342308352
Control17=IDC_EDIT_CZERO,edit,1350631552
Control18=IDC_STATIC_CONE,static,1342308352
Control19=IDC_EDIT_CONE,edit,1350631552
Control20=IDC_STATIC_CTWO,static,1342308352
Control21=IDC_EDIT_CTWO,edit,1350631552

[CLS:DlgLightSetting]
Type=0
HeaderFile=DlgLightSetting.h
ImplementationFile=DlgLightSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_PZ
VirtualFilter=dWC

[DLG:IDD_DLG_GEOMODCREATE]
Type=1
Class=DlgGeoModCreateSetting
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_CTR_A,static,1342308352
Control4=IDC_EDIT_A,edit,1350631552
Control5=IDC_STATIC_CTR_R,static,1342308352
Control6=IDC_EDIT_R,edit,1350631552
Control7=IDC_STATIC_CTR_H,static,1342308352
Control8=IDC_EDIT_H,edit,1350631552
Control9=IDC_STATIC_CTR_RCOUNT,static,1342308352
Control10=IDC_EDIT_RCOUNT,edit,1350631552
Control11=IDC_STATIC_CTR_HCOUNT,static,1342308352
Control12=IDC_EDIT_HCOUNT,edit,1350631552
Control13=IDC_STATIC_CTR_RANGLECOUNT,static,1342308352
Control14=IDC_EDIT_RANGLECOUNT,edit,1350631552
Control15=IDC_STATIC_CTR_ABANGLECOUNT,static,1342308352
Control16=IDC_EDIT_AANGLECOUNT,edit,1350631552
Control17=IDC_EDIT_BANGLECOUNT,edit,1350631552
Control18=IDC_STATIC_CTR_RTWO,static,1342308352
Control19=IDC_EDIT_RTWO,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC_BEZIER_TCOUNT,static,1342308352
Control22=IDC_STATIC_BEZIER_RANGLE,static,1342308352
Control23=IDC_EDIT_BEZIER_TCOUNT,edit,1350631552
Control24=IDC_EDIT_BEZIER_RANGLECOUNT,edit,1350631552
Control25=IDC_STATIC_BEZIER_SPINSETTING,button,1342177287
Control26=IDC_STATIC_GEOMOD_BALLEXLEVEL,static,1342308352
Control27=IDC_EDIT_BALLEX_LEVEL,edit,1350631552

[CLS:DlgGeoModCreateSetting]
Type=0
HeaderFile=DlgGeoModCreateSetting.h
ImplementationFile=DlgGeoModCreateSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_BALLEX_LEVEL
VirtualFilter=dWC

[DLG:IDD_DLG_OPERATIONTIPS]
Type=1
Class=DlgOperationTips
ControlCount=34
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352

[CLS:DlgOperationTips]
Type=0
HeaderFile=DlgOperationTips.h
ImplementationFile=DlgOperationTips.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgOperationTips
VirtualFilter=dWC

[DLG:IDD_DLG_CARTONSETTING]
Type=1
Class=DlgCartonSetting
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_OPENCARTON,button,1342242819
Control4=IDC_CHECK_SPINX,button,1342242819
Control5=IDC_CHECK_SPINY,button,1342242819
Control6=IDC_CHECK_SPINZ,button,1342242819
Control7=IDC_EDIT_SPINX,edit,1350631552
Control8=IDC_EDIT_SPINY,edit,1350631552
Control9=IDC_EDIT_SPINZ,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_UPDATETIME,edit,1350631552

[CLS:DlgCartonSetting]
Type=0
HeaderFile=DlgCartonSetting.h
ImplementationFile=DlgCartonSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT4
VirtualFilter=dWC

[CLS:CComputerGraphicsView]
Type=0
HeaderFile=computergraphicsview.h
ImplementationFile=computergraphicsview.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CComputerGraphicsView

[CLS:CComputerGraphicsDoc]
Type=0
HeaderFile=computergraphicsdoc.h
ImplementationFile=computergraphicsdoc.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC
LastObject=CComputerGraphicsDoc

[CLS:CComputerGraphicsApp]
Type=0
HeaderFile=computergraphics.h
ImplementationFile=computergraphics.cpp
BaseClass=CWinApp
Filter=N
VirtualFilter=AC
LastObject=ID_APP_ABOUT

[DLG:IDD_DLG_BASEOPE]
Type=1
Class=DlgBaseOperationHelp
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352

[CLS:DlgBaseOperationHelp]
Type=0
HeaderFile=DlgBaseOperationHelp.h
ImplementationFile=DlgBaseOperationHelp.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgBaseOperationHelp
VirtualFilter=dWC

