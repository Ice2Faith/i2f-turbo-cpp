using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace Video2AsciiStyle
{
    class Program
    {
        static void Main(string[] args)
        {
            string videoFile = "";
            string saveFile = "";
            int argVideoRate=35;
            int argWidth = 0; 
            int argHeight = 480; 
            int argCharSize = 8; 
            bool argKeepRgb = true;
            if (args.Length < 1)
            {
                showHelp();
                Console.WriteLine("Press enter to exit.");
                Console.Read();
                return;
            }
            if (args.Length >= 1)
            {
                videoFile = args[0];
                saveFile = videoFile + ".asc.mp4";
            }
            if (args.Length >= 2)
            {
                if (args[1] == "-" || args[0]==args[1])
                {
                    saveFile = videoFile + ".asc.mp4";
                }
                else
                {
                    saveFile = args[1];
                }
                
            }
            if (args.Length >= 3)
            {
                argVideoRate = Convert.ToInt32(args[2]);
            }
            if (args.Length >= 4)
            {
                argWidth = Convert.ToInt32(args[3]);
            }
            if (args.Length >= 5)
            {
                argHeight = Convert.ToInt32(args[4]);
            }
            if (args.Length >= 6)
            {
                argCharSize = Convert.ToInt32(args[5]);
            }
            if (args.Length >= 7)
            {
                argKeepRgb = Convert.ToBoolean(args[6]);
            }
            video2AsciiStyle(videoFile,saveFile,argVideoRate,argWidth,argHeight,argCharSize,argKeepRgb);
        }
        public static void showHelp()
        {
            Console.WriteLine("video 2 ascii style command:");
            Console.WriteLine("\tsrcVideoFile [dstVideoFile [videoRate [dstVideoWidth [dstVideoHeight [charSize [keepRgb]]]]]]");
            Console.WriteLine("description:");
            Console.WriteLine("\tsrcVideoFile:[must] source video file");
            Console.WriteLine("\tdstVideoFile:[option] save video file.default=srcVideoFile+'.asc.mp4'");
            Console.WriteLine("\tvideoRate:[option] save video rate.default=35");
            Console.WriteLine("\tdstVideoWidth:[option] save video width.default=0");
            Console.WriteLine("\tdstVideoHeight:[option] save video height.default=480");
            Console.WriteLine("\tcharSize:[option] video charactor size.default=8");
            Console.WriteLine("\tkeepRgb:[option] save video which keep rgb color mode.default=true");
            Console.WriteLine("\twhile dstVideoWidth and dstVideoHeight exist one <=0,the other one will scale by source video rate.");
            Console.WriteLine("usage case:");
            Console.WriteLine("\tC:\\1.mp4");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4 35");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4 35 320");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4 35 320 480");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4 35 0 480 8");
            Console.WriteLine("\tC:\\1.mp4 C:\\2.mp4 35 0 480 8 true");
        }
        public static void callCmdLine(string execFile,string arguments)
        {
            ProcessStartInfo info = new ProcessStartInfo();
            info.FileName = execFile;
            info.Arguments = arguments;
            info.WorkingDirectory = new DirectoryInfo(".\\").FullName;
            info.WindowStyle = ProcessWindowStyle.Hidden;
            Process process=Process.Start(info);
            process.WaitForExit();
        }
        public static void video2AsciiStyle(string videoFile, string saveFile, 
            int argVideoRate=35,
            int argWidth = 0,int argHeight = 640,int argCharSize = 8,bool argKeepRgb = true)
        {
            argWidth = argWidth / argCharSize;
            argHeight = argHeight / argCharSize;
            FileInfo videof = new FileInfo(videoFile);
            if (!videof.Exists)
            {
                Console.WriteLine("源文件不存在：" + videoFile);
                return;
            }
            long startTime = DateTime.Now.Ticks;
            FileInfo savef = new FileInfo(saveFile);
            Console.WriteLine("开始Ascii化视频...");
            Console.WriteLine("\t源文件：" + videof.FullName);
            Console.WriteLine("\t保存到：" + savef.FullName);
            Console.WriteLine("\t帧率：" + argVideoRate);
            Console.WriteLine("\t字符矩阵大小：" + argWidth+","+argHeight);
            Console.WriteLine("\t字符大小：" + argCharSize);
            Console.WriteLine("\t保持RGB：" + argKeepRgb);

            string argWorkPath = ".\\workspace\\";
            string argSrcImgsPath = argWorkPath+videof.Name+"\\srcimgs";
            string argDstImgsPath = argWorkPath+videof.Name + "\\dstimgs";
            string argImgsNameStyle = "image-%8d.jpg";
            string argImgsNameMatcher = "image-*.jpg";
            string argTmpVideoPath = argWorkPath +videof.Name+ "\\tmp.mp4";
            string argExecsPath = ".\\libs\\";
            
            Console.WriteLine("\n分解视频图片帧...");
            DirectoryInfo srcImgsDir = new DirectoryInfo(argSrcImgsPath);
            if (!srcImgsDir.Exists)
            {
                srcImgsDir.Create();
            }
            else
            {
                srcImgsDir.Delete(true);
                srcImgsDir.Create();
            }
            Console.WriteLine("帧率：" + argVideoRate);
            Console.WriteLine("分解：\n\t" + videof.FullName + "\n\t-> " + argSrcImgsPath);
            string video2picturesCmd = string.Format(" -i \"{0}\" -r {1} -f image2 \"{2}\\{3}\"",videof.FullName,argVideoRate,argSrcImgsPath,argImgsNameStyle);

            callCmdLine(argExecsPath+"ffmpeg.exe",video2picturesCmd);
            if (srcImgsDir.GetFiles().Count() == 0)
            {
                Console.WriteLine("视频文件未拆分：" + videoFile);
                return;
            }
            Console.WriteLine("\nAscii化图片帧...");
            FileInfo[] srcImgs = srcImgsDir.GetFiles(argImgsNameMatcher);
            DirectoryInfo dstImgsDir = new DirectoryInfo(argDstImgsPath);
            if (!dstImgsDir.Exists)
            {
                dstImgsDir.Create();
            }
            else
            {
                dstImgsDir.Delete(true);
                dstImgsDir.Create();
            }
            int sumCount = srcImgs.Length;
            int processCount = 0;
            List<Task> taskList = new List<Task>();
            foreach(FileInfo pfile in srcImgs){
                taskList.Add(Task.Run(()=>
                {
                    processCount++;
                    string dstImgs = argDstImgsPath+"\\" + pfile.Name;
                    Console.WriteLine("Ascii 帧："+(((int)(processCount*1.0/sumCount*10000))*1.0/100)+"%  "+processCount+"/"+sumCount+"\n\t" + pfile.FullName + "\n\t-> " + dstImgs);
                    string asciiStyleCmd = string.Format(" \"{0}\" \"{1}\" {2} {3} {4} {5}", pfile.FullName, dstImgs,argWidth,argHeight,argCharSize,argKeepRgb);
                    callCmdLine(argExecsPath + "Picture2AsciiStyle.exe", asciiStyleCmd);
                }));
                
            }
            Task.WaitAll(taskList.ToArray());

            Console.WriteLine("\n图片帧合成视频...");
            FileInfo pTmpfile = new FileInfo(argTmpVideoPath);
            if (pTmpfile.Exists)
            {
                pTmpfile.Delete();
            }
            string pictures2videoCmd = String.Format(" -i \"{0}\\{1}\" -r {2} \"{3}\"",argDstImgsPath,argImgsNameStyle,argVideoRate,argTmpVideoPath);
            callCmdLine(argExecsPath + "ffmpeg.exe", pictures2videoCmd);

            Console.WriteLine("\n视频添加音频...");
            if (!savef.Directory.Exists)
            {
                savef.Directory.Create();
            }
            if (savef.Exists)
            {
                savef.Delete();
            }
            //%FFMPEG_PATH% -i %VIDEO_FILE%  -i %INCLUDE_AUDIO_FILE% -map 0:0 -map 1:1 -c:v:0 copy -c:a:1 copy %DST_FILE%
            string changeVideoMusicCmd = string.Format("-i \"{0}\"  -i \"{1}\" -map 0:0 -map 1:1 -c:v:0 copy -c:a:1 copy \"{2}\"", argTmpVideoPath, videof.FullName, savef.FullName);
            callCmdLine(argExecsPath + "ffmpeg.exe", changeVideoMusicCmd);
            //string changeVideoMusicCmd = string.Format(" \"{0}\" \"{1}\" \"{2}\"", argTmpVideoPath, videof.FullName, savef.FullName);
            //callCmdLine(argExecsPath + "chvm.exe", changeVideoMusicCmd);
            
            Console.WriteLine("\n等待结束处理....");
            Thread.Sleep(300);
            string saveFilePath = savef.FullName;
            int waitTimes=0;
            while (!new FileInfo(saveFilePath).Exists)
            {
                Console.WriteLine("\t\t等待轮："+waitTimes);
                Thread.Sleep(300);
                waitTimes++;
            }
            
            Console.WriteLine("\n清理过程文件...");
            DirectoryInfo delDir = new DirectoryInfo(argWorkPath + videof.Name);
            delDir.Delete(true);

            long endTime = DateTime.Now.Ticks;
            Console.WriteLine("\n用时：" + ((endTime - startTime) / 1000.0) + "s");
            
            Console.WriteLine("\n视频Ascii化完毕.");
            Console.WriteLine("\n文件保存到：\n\t" + savef.FullName);
        }
        
    }
}
