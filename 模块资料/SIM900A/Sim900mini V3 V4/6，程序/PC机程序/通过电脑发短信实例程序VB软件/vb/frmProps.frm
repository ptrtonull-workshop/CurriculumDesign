VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form form4 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "ͨ�Ŷ˿�����"
   ClientHeight    =   4260
   ClientLeft      =   4140
   ClientTop       =   1665
   ClientWidth     =   6015
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4260
   ScaleWidth      =   6015
   ShowInTaskbar   =   0   'False
   Begin VB.Frame fraSettings 
      BorderStyle     =   0  'None
      Height          =   3495
      Left            =   255
      TabIndex        =   1
      Top             =   570
      Width           =   5445
      Begin VB.CommandButton cmdCancel 
         Caption         =   "ȡ��"
         Height          =   300
         Left            =   4335
         TabIndex        =   22
         Top             =   1065
         Width           =   1080
      End
      Begin VB.Frame Frame1 
         Caption         =   "����ٶ�"
         Height          =   870
         Left            =   180
         TabIndex        =   20
         Top             =   630
         Width           =   2340
         Begin VB.ComboBox cboSpeed 
            Height          =   315
            Left            =   375
            Style           =   2  'Dropdown List
            TabIndex        =   21
            Top             =   330
            Width           =   1695
         End
      End
      Begin VB.Frame fraConnection 
         Caption         =   "�Ż�����"
         Height          =   1770
         Left            =   180
         TabIndex        =   12
         Top             =   1635
         Width           =   2325
         Begin VB.ComboBox cboStopBits 
            Height          =   315
            Left            =   1050
            Style           =   2  'Dropdown List
            TabIndex        =   16
            Top             =   1260
            Width           =   1140
         End
         Begin VB.ComboBox cboParity 
            Height          =   315
            Left            =   1050
            Style           =   2  'Dropdown List
            TabIndex        =   15
            Top             =   810
            Width           =   1140
         End
         Begin VB.ComboBox cboDataBits 
            Height          =   315
            Left            =   1050
            Style           =   2  'Dropdown List
            TabIndex        =   14
            Top             =   330
            Width           =   1140
         End
         Begin VB.Label Label5 
            Caption         =   "ֹͣλ:"
            Height          =   285
            Left            =   180
            TabIndex        =   19
            Top             =   1320
            Width           =   885
         End
         Begin VB.Label Label4 
            Caption         =   "��żλ:"
            Height          =   285
            Left            =   180
            TabIndex        =   18
            Top             =   855
            Width           =   735
         End
         Begin VB.Label Label3 
            Caption         =   "����λ:"
            Height          =   285
            Left            =   180
            TabIndex        =   17
            Top             =   375
            Width           =   825
         End
      End
      Begin VB.ComboBox cboPort 
         Height          =   315
         Left            =   900
         Style           =   2  'Dropdown List
         TabIndex        =   11
         Top             =   150
         Width           =   1425
      End
      Begin VB.CommandButton cmdOK 
         Caption         =   "ȷ��"
         Default         =   -1  'True
         Height          =   300
         Left            =   4335
         MaskColor       =   &H00000000&
         TabIndex        =   10
         Top             =   705
         Width           =   1080
      End
      Begin VB.Frame Frame7 
         Caption         =   "��Ӧ(&E)"
         Height          =   870
         Left            =   2595
         TabIndex        =   7
         Top             =   630
         Width           =   1590
         Begin VB.OptionButton optEcho 
            Caption         =   "�ر�"
            Height          =   315
            Index           =   0
            Left            =   135
            MaskColor       =   &H00000000&
            TabIndex        =   9
            Top             =   360
            Width           =   735
         End
         Begin VB.OptionButton optEcho 
            Caption         =   "��"
            Height          =   195
            Index           =   1
            Left            =   840
            MaskColor       =   &H00000000&
            TabIndex        =   8
            Top             =   420
            Width           =   675
         End
      End
      Begin VB.Frame Frame5 
         Caption         =   "������(&F)"
         Height          =   1770
         Left            =   2595
         TabIndex        =   2
         Top             =   1635
         Width           =   1620
         Begin VB.OptionButton optFlow 
            Caption         =   "û��"
            Height          =   255
            Index           =   0
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   6
            Top             =   360
            Value           =   -1  'True
            Width           =   855
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "Xon/Xoff"
            Height          =   255
            Index           =   1
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   5
            Top             =   645
            Width           =   1095
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "RTS"
            Height          =   255
            Index           =   2
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   4
            Top             =   945
            Width           =   735
         End
         Begin VB.OptionButton optFlow 
            Caption         =   "Xon/RTS"
            Height          =   255
            Index           =   3
            Left            =   180
            MaskColor       =   &H00000000&
            TabIndex        =   3
            Top             =   1245
            Width           =   1155
         End
      End
      Begin VB.Label Label1 
         Caption         =   "�˿�:"
         Height          =   315
         Left            =   330
         TabIndex        =   13
         Top             =   180
         Width           =   495
      End
   End
   Begin MSComctlLib.TabStrip tabSettings 
      Height          =   4065
      Left            =   90
      TabIndex        =   0
      Top             =   105
      Width           =   5820
      _ExtentX        =   10266
      _ExtentY        =   7170
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   1
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "����"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private iFlow As Integer, iTempEcho As Boolean


Sub LoadPropertySettings()
Dim i As Integer, Settings As String, Offset As Integer

' ����˿�����
For i = 1 To 16
    cboPort.AddItem "Com" & Trim$(Str$(i))
Next i

' Load Speed Settings
cboSpeed.AddItem "110"
cboSpeed.AddItem "300"
cboSpeed.AddItem "600"
cboSpeed.AddItem "1200"
cboSpeed.AddItem "2400"
cboSpeed.AddItem "4800"
cboSpeed.AddItem "9600"
cboSpeed.AddItem "14400"
cboSpeed.AddItem "19200"
cboSpeed.AddItem "28800"
cboSpeed.AddItem "38400"
cboSpeed.AddItem "56000"
cboSpeed.AddItem "57600"
cboSpeed.AddItem "115200"
cboSpeed.AddItem "128000"
cboSpeed.AddItem "256000"

' ��������λ����
cboDataBits.AddItem "4"
cboDataBits.AddItem "5"
cboDataBits.AddItem "6"
cboDataBits.AddItem "7"
cboDataBits.AddItem "8"

' ������ż��������
cboParity.AddItem "Even"
cboParity.AddItem "Odd"
cboParity.AddItem "None"
cboParity.AddItem "Mark"
cboParity.AddItem "Space"

' ����ֹͣλ����
cboStopBits.AddItem "1"
cboStopBits.AddItem "1.5"
cboStopBits.AddItem "2"

' ����Ĭ�ϵ�����

Settings = form1.MSComm1.Settings

' �ڴ��������£��ұߵĴ󲿷����ý�Ϊһ���ַ�
' ���˿��ܳ��ֵ� 1.5 ֹͣλ.
If InStr(Settings, ".") > 0 Then
    Offset = 2
Else
    Offset = 0
End If

cboSpeed.text = Left$(Settings, Len(Settings) - 6 - Offset)
Select Case Mid$(Settings, Len(Settings) - 4 - Offset, 1)
Case "e"
    cboParity.ListIndex = 0
Case "m"
    cboParity.ListIndex = 1
Case "n"
    cboParity.ListIndex = 2
Case "o"
    cboParity.ListIndex = 3
Case "s"
    cboParity.ListIndex = 4
End Select

cboDataBits.text = Mid$(Settings, Len(Settings) - 2 - Offset, 1)
cboStopBits.text = Right$(Settings, 1 + Offset)
    
cboPort.ListIndex = form1.MSComm1.CommPort - 1

optFlow(form1.MSComm1.Handshaking).Value = True
If Echo Then
    optEcho(1).Value = True
Else
    optEcho(0).Value = True
End If

End Sub


Private Sub cmdCancel_Click()
Unload Me
End Sub

Private Sub cmdOK_Click()
Dim OldPort As Integer, ReOpen As Boolean

On Error Resume Next

Echo = iTempEcho
OldPort = form1.MSComm1.CommPort
NewPort = cboPort.ListIndex + 1

If NewPort <> OldPort Then                   ' ����˿ںű�����, �ر�ԭ���Ķ˿ڡ�
    If form1.MSComm1.PortOpen Then
           form1.MSComm1.PortOpen = False
           ReOpen = True
    End If

    form1.MSComm1.CommPort = NewPort          ' �����µĶ˿ںš�
    
    If Err = 0 Then
        If ReOpen Then
            form1.MSComm1.PortOpen = True
            'Form1.mnuOpen.Checked = Form1.MSComm1.PortOpen
            'Form1.mnuSendText.Enabled = Form1.MSComm1.PortOpen
            'Form1.tbrToolBar.Buttons("TransmitTextFile").Enabled = Form1.MSComm1.PortOpen
        End If
    End If
        
    If Err Then
        MsgBox Error$, 48
        form1.MSComm1.CommPort = OldPort
        Exit Sub
    End If
End If


form1.MSComm1.Settings = Trim$(cboSpeed.text) & "," & Left$(cboParity.text, 1) _
    & "," & Trim$(cboDataBits.text) & "," & Trim$(cboStopBits.text)

If Err Then
    MsgBox Error$, 48
    Exit Sub
End If

form1.MSComm1.Handshaking = iFlow
If Err Then
    MsgBox Error$, 48
    Exit Sub
End If

SaveSetting App.Title, "����", "����", form1.MSComm1.Settings
SaveSetting App.Title, "����", "ͨ�Ŷ˿�", form1.MSComm1.CommPort
SaveSetting App.Title, "����", "����", form1.MSComm1.Handshaking
SaveSetting App.Title, "����", "��Ӧ", Echo

form1.Command1.Enabled = True

Unload Me

End Sub

Private Sub Form_Load()

' ���ô���ߴ�
Me.Left = (Screen.Width - Me.Width) / 2
Me.Top = (Screen.Height - Me.Height) / 2

' �����߿����ʺ�ѡ��ؼ�
fraSettings.Move tabSettings.ClientLeft, tabSettings.ClientTop

' ȷ���߿�λ�ڶ����ؼ��Ķ���
fraSettings.ZOrder

' ���뵱ǰ����������
LoadPropertySettings

End Sub




Private Sub optEcho_Click(Index As Integer)
If Index = 1 Then
    iTempEcho = True
Else
    iTempEcho = False
End If
End Sub

Private Sub optFlow_Click(Index As Integer)
iFlow = Index
End Sub


