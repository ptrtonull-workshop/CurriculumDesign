VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Frm_MultiTCP 
   Caption         =   "SIM300 GRPS�ͻ������ӳ��� ���ݾ��ص������޹�˾"
   ClientHeight    =   6570
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7035
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6570
   ScaleWidth      =   7035
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton Command4 
      Caption         =   "�����ʾ"
      Height          =   375
      Left            =   5280
      TabIndex        =   17
      Top             =   1800
      Width           =   1095
   End
   Begin VB.Timer Timer1 
      Interval        =   500
      Left            =   3120
      Top             =   5640
   End
   Begin VB.CommandButton Command3 
      Caption         =   "�Ͽ�"
      Height          =   375
      Left            =   5520
      TabIndex        =   9
      Top             =   720
      Width           =   855
   End
   Begin VB.TextBox Text4 
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      TabIndex        =   8
      Text            =   "1001"
      Top             =   720
      Width           =   855
   End
   Begin VB.TextBox Text3 
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   720
      TabIndex        =   7
      Text            =   "192.168.1.101"
      Top             =   720
      Width           =   2055
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H8000000A&
      Caption         =   "����"
      Height          =   375
      Left            =   4200
      TabIndex        =   6
      Top             =   720
      Width           =   975
   End
   Begin VB.TextBox Text2 
      Height          =   3375
      Left            =   720
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   2
      Top             =   2280
      Width           =   5655
   End
   Begin VB.CommandButton Command1 
      Caption         =   "������Ϣ"
      Height          =   375
      Left            =   5280
      TabIndex        =   1
      Top             =   1320
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   720
      TabIndex        =   0
      Top             =   1320
      Width           =   4335
   End
   Begin MSWinsockLib.Winsock WSK_Server 
      Index           =   0
      Left            =   120
      Top             =   3840
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label10 
      Caption         =   "���ݾ��ص������޹�˾   http://www.hificat.com   Email:hificat@163.com"
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Top             =   6240
      Width           =   6495
   End
   Begin VB.Line Line2 
      X1              =   720
      X2              =   6360
      Y1              =   6120
      Y2              =   6120
   End
   Begin VB.Label Label9 
      Caption         =   "��"
      Height          =   255
      Left            =   4080
      TabIndex        =   15
      Top             =   1920
      Width           =   735
   End
   Begin VB.Label Label8 
      Caption         =   "��"
      Height          =   255
      Left            =   2160
      TabIndex        =   14
      Top             =   1920
      Width           =   1815
   End
   Begin VB.Label Label7 
      Caption         =   "Label7"
      Height          =   255
      Left            =   5640
      TabIndex        =   13
      Top             =   5880
      Width           =   855
   End
   Begin VB.Label Label6 
      Caption         =   "�����ӿͻ��ˣ�"
      Height          =   255
      Left            =   4200
      TabIndex        =   12
      Top             =   5880
      Width           =   1455
   End
   Begin VB.Label Label5 
      Caption         =   "Label5"
      Height          =   255
      Left            =   1320
      TabIndex        =   11
      Top             =   5880
      Width           =   735
   End
   Begin VB.Label Label4 
      Caption         =   "״̬��"
      Height          =   255
      Left            =   720
      TabIndex        =   10
      Top             =   5880
      Width           =   615
   End
   Begin VB.Line Line1 
      X1              =   720
      X2              =   6360
      Y1              =   5760
      Y2              =   5760
   End
   Begin VB.Label Label3 
      Caption         =   "�˿ں�"
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3000
      TabIndex        =   5
      Top             =   360
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "����IP��ַ"
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   840
      TabIndex        =   4
      Top             =   360
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "���ܵ�����Ϣ"
      Height          =   255
      Left            =   720
      TabIndex        =   3
      Top             =   1920
      Width           =   1095
   End
End
Attribute VB_Name = "Frm_MultiTCP"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim ClientNum As Integer
'��ʱ US
Public Sub Delay(mSec As Long)
  On Error Resume Next
            
          Dim TStart     As Single
            
          TStart = Timer
            
          While (Timer - TStart) < (mSec / 1000)
                  DoEvents
          Wend
    
    
  End Sub

Private Sub Command1_Click()
Dim i As Integer
Dim j As Integer
    For i = 1 To ClientNum
        If Not WSK_Server(i) Is Nothing Then
            DoEvents
            j = WSK_Server(i).State
            If j = 7 Then
              ' WSK_Server(i).SendData "������:" & Text1.Text
               WSK_Server(i).SendData Text1.Text
          Else
            WSK_Server(i).Close
           End If
        End If
    Next
End Sub

Private Sub Command2_Click()
   Dim i As Integer
   
    Text4.BackColor = &H80000000
     Text3.BackColor = &H80000000
     Label8.Caption = "��"
     Label9.Caption = "��"
     
   i = WSK_Server(0).State
   If i = 2 Then
        Label5.Caption = "������"
        Exit Sub
   End If
   WSK_Server(0).LocalPort = Text4.Text
    WSK_Server(0).RemoteHost = Text3.Text
    '��������ʱ����
    WSK_Server(0).Listen
    Delay (10)
    ' Delay (500)
    '  Delay (1000)
      
   i = WSK_Server(0).State
   If i = 2 Then
    Label5.Caption = "������"
    End If
End Sub

Private Sub Command3_Click()
    
   Dim i As Integer
Dim j As Integer
   Text4.BackColor = &H80000005
   Text3.BackColor = &H80000005
    For i = 1 To ClientNum
        If Not WSK_Server(i) Is Nothing Then
            DoEvents
            
           ' WSK_Server(i).Close
           '  WSK_Server(i) = Nothing
             Unload WSK_Server(i)
        End If
    Next
    WSK_Server(0).Close
   'WSK_Server.Close
     Label5.Caption = "�ѶϿ�"
     Label8.Caption = "��"
     Label9.Caption = "��"
     ClientNum = 0
End Sub

Private Sub Command4_Click()
      Text2.Text = ""
End Sub

Private Sub Form_Load()
  Label5.Caption = "�ѶϿ�"
   Label7.Caption = Str(ClientNum)
'  WSK_Server(0).LocalPort = 1001
    '��������ʱ����
  '  WSK_Server(0).Listen
End Sub

Private Sub Timer1_Timer()

   Label7.Caption = Str(ClientNum)
End Sub

Private Sub WSK_Server_Close(Index As Integer)
  
  ' Unload WSK_Server(Index)
    'Set WSK_Server(Index) = Nothing
  'WSK_Server(iIndex).Close

 
End Sub

Private Sub WSK_Server_ConnectionRequest(Index As Integer, ByVal requestID As Long)
    Dim i As Integer
    ClientNum = ClientNum + 1
 
     
           Load WSK_Server(ClientNum)  '����һ���µ�socket�ؼ�
            WSK_Server(ClientNum).Accept requestID  '���ܿͻ��˵�����
            WSK_Server(ClientNum).SendData "Welcome To KinCony ELECTRONICS:"
     
    
  
    
 
            
End Sub

Private Sub WSK_Server_DataArrival(Index As Integer, ByVal bytesTotal As Long)
Dim myData As String
   Label8.Caption = WSK_Server(Index).RemoteHostIP
   
   Label9.Caption = WSK_Server(Index).RemotePort
   
    WSK_Server(Index).GetData myData
    Text2.Text = Text2.Text + myData + vbCrLf
    
End Sub

Private Sub WSK_Server_Error(Index As Integer, ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    WSK_Server(Index).Close
     Unload WSK_Server(Index)
   ' Set WSK_Server(Index) = Nothing
End Sub
