MKDIR E:\Autorun.inf
CHDIR E:\Autorun.inf
MKDIR E:\Autorun.inf\Immune...\\
attrib +r +h E:\Autorun.inf
MKDIR E:\Auto.exe
CHDIR E:\Auto.exe
MKDIR E:\Auto.exe\Immune...\\
attrib +r +h E:\Auto.exe
MKDIR E:\System.exe
CHDIR E:\System.exe
MKDIR E:\System.exe\Immune...\\
attrib +r +h E:\System.exe
DEL %0
exit
