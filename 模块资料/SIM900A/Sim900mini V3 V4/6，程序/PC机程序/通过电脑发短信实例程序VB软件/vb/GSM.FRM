VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form form1 
   Caption         =   "杭州晶控电子有限公司  http://www.hificat.com"
   ClientHeight    =   4755
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6960
   LinkTopic       =   "Form1"
   ScaleHeight     =   4755
   ScaleWidth      =   6960
   StartUpPosition =   3  '窗口缺省
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   5160
      Top             =   960
   End
   Begin VB.TextBox Text2 
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   2160
      TabIndex        =   9
      Top             =   2025
      Visible         =   0   'False
      Width           =   3855
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   300
      Left            =   480
      Top             =   1080
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   1080
      Top             =   960
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      RThreshold      =   1
      RTSEnable       =   -1  'True
      SThreshold      =   1
   End
   Begin VB.CommandButton Command6 
      Caption         =   "高级"
      Enabled         =   0   'False
      Height          =   495
      Left            =   480
      TabIndex        =   7
      Top             =   3840
      Width           =   855
   End
   Begin VB.TextBox Text1 
      ForeColor       =   &H00FF0000&
      Height          =   1815
      Left            =   2160
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      TabIndex        =   6
      Top             =   2520
      Visible         =   0   'False
      Width           =   3855
   End
   Begin VB.CommandButton Command5 
      Caption         =   "属性"
      Height          =   495
      Left            =   480
      TabIndex        =   5
      Top             =   3240
      Width           =   855
   End
   Begin VB.CommandButton Command4 
      Caption         =   "短信"
      Enabled         =   0   'False
      Height          =   495
      Left            =   480
      MaskColor       =   &H8000000F&
      TabIndex        =   4
      Top             =   2640
      Width           =   855
   End
   Begin VB.CommandButton Command3 
      Caption         =   "信息"
      Enabled         =   0   'False
      Height          =   495
      Left            =   480
      MaskColor       =   &H8000000F&
      TabIndex        =   3
      Top             =   2040
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      Caption         =   "断开"
      Enabled         =   0   'False
      Height          =   495
      Left            =   3840
      TabIndex        =   2
      Top             =   960
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "连接"
      Enabled         =   0   'False
      Height          =   495
      Left            =   2160
      TabIndex        =   1
      Top             =   960
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "短信DEMO测试程序"
      Height          =   1455
      Left            =   2280
      TabIndex        =   8
      Top             =   2640
      Width           =   3615
   End
   Begin VB.Line Line2 
      X1              =   1680
      X2              =   1680
      Y1              =   1680
      Y2              =   4440
   End
   Begin VB.Line Line1 
      X1              =   360
      X2              =   6360
      Y1              =   1680
      Y2              =   1680
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "西门子 Siemens TC35系列开发板DEMO程序"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   240
      Left            =   1200
      TabIndex        =   0
      Top             =   480
      Width           =   4845
   End
End
Attribute VB_Name = "form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim out As Variant
Dim disp As String



Private Sub Command1_Click()
MSComm1.PortOpen = True
Command2.Enabled = True
Command1.Enabled = False
Command3.Enabled = True
command4.Enabled = True
Command6.Enabled = True
MSComm1.Output = "AT" & vbCr
'Timer2.Enabled = True

MSComm1.Output = "AT+CNMI=2,2" & vbCr
MSComm1.Output = "AT+CMGF=0" & vbCr

End Sub
Private Sub Command2_Click()
MSComm1.PortOpen = False
Command2.Enabled = False
Command1.Enabled = True
Command3.Enabled = False
command4.Enabled = False
Command6.Enabled = False
Unload Form2
Unload Form3
Unload form4
Text1.Visible = False
Text2.Visible = False
End Sub

Private Sub Command3_Click()
Form3.Show
End Sub

Private Sub command4_Click()
Form2.Show
End Sub

Private Sub Command5_Click()

form4.Show vbModal
End Sub

Private Sub Command6_Click()
Text1.Visible = Not Text1.Visible
Text2.Visible = Not Text2.Visible
End Sub



Private Sub Form_Load()
'MSComm1.CommPort = 2
'MSComm1.Settings = "19200,n,8,1"
'MSComm1.Handshaking = comNone
form1.Show
Set allflag = form1.Text1



End Sub

Private Sub MSComm1_OnComm() '处理串口事件

 Select Case MSComm1.CommEvent
        ' 事件信息
        Case comEvReceive
            'MsgBox "comEvReceive"
            Timer1.Enabled = True
            'Timer2.Enabled = True
           
        Case comEvSend
               ' Dim Buffer As Variant
          ' Buffer = MSComm1.Input
            'MsgBox "comEvSend"
            
        Case comEvCTS
            'MsgBox "被检测的 CTS 改变"
        Case comEvDSR
            'MsgBox "被检测的 DSR 改变"
        Case comEvCD
            'MsgBox "被检测的 CD 改变"
        Case comEvRing
            'MsgBox "电话铃响起"
        Case comEvEOF
            'MsgBox "被检测的文件结尾"

        ' Error messages.
        Case comBreak
            ERMsg$ = "收到中断"
        Case comCDTO
            ERMsg$ = "运输检测超时"
        Case comCTSTO
            ERMsg$ = "CTS 超时"
        Case comDCB
            ERMsg$ = "检索 DCB 错误"
        Case comDSRTO
            ERMsg$ = "DSR 超时"
        Case comFrame
            ERMsg$ = "帧错误"
        Case comOverrun
            ERMsg$ = "超限错误"
        Case comRxOver
            ERMsg$ = "接收缓冲区溢出"
        Case comRxParity
            ERMsg$ = "奇偶校验错"
        Case comTxFull
            ERMsg$ = "传送缓冲区满"
        Case Else
            ERMsg$ = "未知的错误或事件"
    End Select

End Sub
Public Function show_f(data As String) As String
'显示函数，处理从串口返回的数据
Dim TermSize As Long, i
  ' TermSize = 1
   
    ' 过滤/处理空格符。
    Do
       i = InStr(data, Chr$(8))
       If i Then
          If i = 1 Then
             'Term.SelStart = TermSize - 1
             'Term.SelLength = 1
             data = Mid$(data, i + 1)
          Else
             data = Left$(data, i - 2) & Mid$(data, i + 1)
          End If
       End If
    Loop While i

    ' 除去换行符。
    Do
       i = InStr(data, Chr$(10))
       If i Then
          data = Left$(data, i - 1) & Mid$(data, i + 1)
       End If
    Loop While i

    ' 除去换行符用空格符替代。
    i = 0
    Do
       i = InStr(i + 1, data, Chr$(13))
       If i Then
          data = Left$(data, i - 1) & Mid$(data, i + 1)
       End If
    Loop While i


    ' 返回数据。
    show_f = data
   ' Label1.Caption = Data
End Function

Private Static Sub show_s(Term As Control, data As String)
'显示模块，用于显示从串口返回的数据
Dim TermSize, i As Integer
TermSize = Len(Term.text)
   
    ' 过滤/处理退格符。
    Do
       i = InStr(data, Chr$(8))
       If i Then
          If i = 1 Then
             Term.SelStart = TermSize - 1
             Term.SelLength = 1
             data = Mid$(data, i + 1)
          Else
             data = Left$(data, i - 2) & Mid$(data, i + 1)
       End If
       End If
    Loop While i

    ' 除去换行符。
    Do
       i = InStr(data, Chr$(10))
       If i Then
          data = Left$(data, i - 1) & Mid$(data, i + 1)
       End If
    Loop While i

    ' 确定所有的回车都包含换行符。
    i = 0
    Do
       i = InStr(i + 1, data, Chr$(13))
       If i Then
          data = Left$(data, i) & Chr$(10) & Mid$(data, i + 1)
       End If
       
    Loop While i

    ' 添加过滤的数据到 SelText 属性。
    Term.SelText = data
   ' Label1.Caption = Data
    
End Sub
Public Function show_f1(data As String) As String
Dim datasize, i, j, k As Integer
Dim data_l, data_m, data_r As String
datasize = Len(data)

   
    ' 过滤/处理退格符。
    Do
       i = InStr(data, Chr$(8))
       If i Then
          If i = 1 Then
             data = "-" & Mid$(data, i + 1)
          Else
             data = Left$(data, i - 1) & Mid$(data, i + 1)
          End If
       End If
    Loop While i
    

    ' 确定所有的回车都包含换行符。
    i = 1
    j = 0
    k = 0
    Do
        i = InStr(i, data, Chr$(13))
        j = InStr(i + 1, data, Chr$(13))
        If j - i = 1 Then
            data_l = Left(data, i - 1)
            data = Mid(data, j + 1)
        End If
        If i Then data = Left$(data, i - 1) & Mid$(data, i + 1)
  
    Loop While i
    
        ' 除去换行符。
    Do
       i = InStr(data, Chr$(10))
       If i Then
          data = Left$(data, i - 1) & Mid$(data, i + 1)
       End If
    Loop While i

    
    If data_l <> "" Then
        k = InStr(data, "OK")
        If k Then
            data_m = Left(data, k - 1)
            data_r = Mid(data, k)
        End If
    End If
MsgBox "data_l=>" & data_l
MsgBox "data_m=>" & data_m
MsgBox "data_r=>" & data_r
'MsgBox "data=>" & data

End Function

Private Sub optFlow_Click(Index As Integer)
iFlow = Index
End Sub

Private Sub Text2_Change() '处理命令
Dim key As String
Dim key1 As Integer
key = Right(Text2.text, 1)
    If MSComm1.PortOpen Then
        If key <> "" Then
            key1 = AscW(key)
            Select Case key1
                Case 8
                    SendKeys "{BACKSPACE}"
                Case 47
                    out = out & Chr$(47)
                    MSComm1.Output = out
                    Timer1.Enabled = True
                    out = Null
                    Text2.text = ""
                    Set allflag = form1.Text1
                Case Else
                    out = Text2.text
            End Select
        End If
    End If
End Sub

Private Sub Text2_KeyPress(KeyAscii As Integer) '命令中的回车及CTRL＿Z
   If MSComm1.PortOpen Then
        If KeyAscii = 13 Then
            out = out & vbCr
            MSComm1.Output = out
            Timer1.Enabled = True
            out = Null
            Text2.text = ""
            Set allflag = form1.Text1
        End If
        If KeyAscii = 26 Then
            out = out & Chr$(26)
            MSComm1.Output = out
            Timer1.Enabled = True
            out = Null
            Text2.text = ""
            Set allflag = form1.Text1
        End If
        
    End If
    'KeyAscii = 0
End Sub

Private Sub Timer1_Timer() '用于等待MODEM回应的延时
Dim buffer As Variant
Dim lenbuffer As Integer

disp = ""
Timer1.Enabled = False
buffer = MSComm1.Input
lenbuffer = Len(buffer)
'disp = show_f1(CStr(buffer
If lenbuffer <> 0 Then
    Call show_s(allflag, CStr(buffer))
    Call receive(CStr(buffer))
    End If
End Sub

Private Sub Timer2_Timer()
Timer2.Enabled = False
Dim buffer As Variant
buffer = MSComm1.Input
Call receive(CStr(buffer))
End Sub

Public Sub receive(indata As String) '接收短信子程序
Dim receive_ok As String
Dim i, j As Integer

If indata = "" Then Exit Sub

j = Len(indata)
'Call show_s(allflag, CStr(indata))


i = InStr(indata, "+CMT:")
If i Then
    receive_ok = Right(indata, j - i + 4)
    Dim i1, i2, i3, i4 As Integer
    Dim cal, tim, text As String
    
    Dim ii As Integer
    Dim aa, bb, cc, c1, c2 As String
    
    Dim jj As String
    Dim kk As Integer
    
    i1 = InStr(receive_ok, Chr$(34))
    If i1 Then
        i2 = InStr(i1 + 1, receive_ok, Chr$(34))
        i3 = InStr(i2 + 1, receive_ok, Chr$(34))
        i4 = InStr(i3 + 1, receive_ok, Chr$(34))
        cal = Mid(receive_ok, i1 + 1, i2 - i1 - 1)
        tim = Mid(receive_ok, i3 + 1, i4 - i3 - 1)
        text = Mid(receive_ok, i4 + 3)
        MsgBox "主叫号码-> " & cal & vbCr & "接收时间-> " & tim & vbCr & "信息内容-> " & text
        Else
            i2 = InStr(receive_ok, "F") '处理主叫号码
            aa = Mid(receive_ok, i2 + 4, 2)
            If aa = "0D" Then
                cal = Mid(receive_ok, i2 + 8, 14)
                For ii = 1 To 14 Step 2
                    bb = Mid(cal, ii, 2)
                    c1 = Left(bb, 1)
                    c2 = Right(bb, 1)
                    cc = cc & c2 & c1
                    
                Next
                cal = "+" & Mid(cc, 1, 13)
            End If
            If aa = "OB" Then
                cal = Mid(receive_ok, i2 + 8, 12)
                For ii = 1 To 12 Step 2
                    bb = Mid(cal, ii, 2)
                    c1 = Left(bb, 1)
                    c2 = Right(bb, 1)
                    cc = cc & c2 & c1
                Next
                cal = Mid(cc, 1, 11)
            End If
            
            cc = ""
            i2 = InStr(i2 + 1, receive_ok, "F") '处理接收时间
            tim = Mid(receive_ok, i2 + 6, 14)
            For ii = 1 To 14 Step 2
                bb = Mid(tim, ii, 2)
                c1 = Left(bb, 1)
                c2 = Right(bb, 1)
                If ii = 3 Or ii = 5 Then cc = cc & "/"
                If ii = 7 Then cc = cc & ","
                If ii = 9 Or ii = 11 Then cc = cc & ":"
                If ii = 13 Then cc = cc & "+"
                cc = cc & c2 & c1
            Next
            tim = cc
            
            cc = ""
            aa = Mid(receive_ok, i2 + 4, 2) '处理信息内容
            text = Mid(receive_ok, i2 + 22)
            If aa = "08" Then '收到中中文短信
                jj = Mid(receive_ok, i2 + 20, 2) '字符个数
                kk = Val("&h" & jj) '变成十进制
                For ii = 1 To (kk / 2)
                    bb = Mid(text, (ii - 1) * 4 + 1, 4)
                    cc = cc & ChrW(Val("&h" & bb))
                Next
                text = cc
            End If
            If aa = "00" Then '收到手机发来的7比特西文短信
                jj = Mid(receive_ok, i2 + 20, 2) '字符个数
                kk = Val("&h" & jj) '变成十进制
                jj = InStr(text, vbCr)
                text = Left(text, jj - 1) '去掉内容后面的回车符
                jj = Len(text)
                For ii = (jj / 2) To 1 Step -1
                    bb = Mid(text, ii * 2 - 1, 2)
                    cc = cc & bb
                Next
                text = cc
                cc = ""
                For ii = 1 To jj
                    bb = Mid(text, i, 1)
                    Select Case bb
                        Case "0"
                            cc = cc & "0000"
                        Case "1"
                            cc = cc & "0001"
                        Case "2"
                            cc = cc & "0010"
                        Case "3"
                            cc = cc & "0011"
                        Case "4"
                            cc = cc & "0100"
                        Case "5"
                            cc = cc & "0101"
                        Case "6"
                            cc = cc & "0110"
                        Case "7"
                            cc = cc & "0111"
                        Case "8"
                            cc = cc & "1000"
                        Case "9"
                            cc = cc & "1001"
                        Case "A"
                            cc = cc & "1010"
                        Case "B"
                            cc = cc & "1011"
                        Case "C"
                            cc = cc & "1100"
                        Case "D"
                            cc = cc & "1101"
                        Case "E"
                            cc = cc & "1110"
                        Case "F"
                            cc = cc & "1111"
                    End Select
                Next
                text = cc
                cc = ""
                For ii = kk To 1 Step -1
                    bb = "0" & Mid(text, ii * 7 - 7, 7)
                    cc = cc & Str(Val("&b" & bb))
                Next
                text = cc
            End If
                                
                
                
            MsgBox "主叫号码-> " & cal & vbCr & "接收时间-> " & tim & vbCr & "信息内容-> " & text
    End If
End If

i = 0
i = InStr(indata, "+CMGS:")
If i Then Call show_s(allflag, "发送短信成功")



End Sub

