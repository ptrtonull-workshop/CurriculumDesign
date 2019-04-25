VERSION 5.00
Begin VB.Form Form3 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "信息"
   ClientHeight    =   2235
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5745
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2235
   ScaleWidth      =   5745
   StartUpPosition =   3  '窗口缺省
   Begin VB.TextBox Text5 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   300
      Left            =   1320
      TabIndex        =   9
      Top             =   1680
      Width           =   3800
   End
   Begin VB.TextBox Text4 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      Height          =   315
      Left            =   1320
      TabIndex        =   8
      Top             =   1320
      Width           =   3800
   End
   Begin VB.TextBox Text3 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1320
      TabIndex        =   7
      Top             =   960
      Width           =   3800
   End
   Begin VB.CommandButton Command5 
      Caption         =   "硬件版本"
      Height          =   350
      Left            =   240
      TabIndex        =   6
      Top             =   1680
      Width           =   975
   End
   Begin VB.CommandButton command4 
      Caption         =   "出厂日期"
      Height          =   350
      Left            =   240
      TabIndex        =   5
      Top             =   1320
      Width           =   975
   End
   Begin VB.CommandButton Command3 
      Caption         =   "设备序号"
      Height          =   350
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   975
   End
   Begin VB.TextBox Text2 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1320
      TabIndex        =   3
      Top             =   600
      Width           =   3800
   End
   Begin VB.CommandButton Command2 
      Caption         =   "设备类型"
      Height          =   350
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000007&
      Height          =   315
      Left            =   1320
      TabIndex        =   1
      Top             =   240
      Width           =   3800
   End
   Begin VB.CommandButton Command1 
      Caption         =   "生产厂商"
      Height          =   350
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False



Private Sub Command1_Click()
Form3.Text1 = " "
Form1.MSComm1.Output = "AT+CGMI" & Chr$(13)
Set allflag = Form3.Text1
'Form1.Timer1.Enabled = True

End Sub

Private Sub Command2_Click()
Form3.Text2 = " "

Form1.MSComm1.Output = "AT+CGMM" & Chr$(13)
Set allflag = Form3.Text2
'Form1.Timer1.Enabled = True

End Sub

Private Sub Command3_Click()
Form3.Text3 = " "
Form1.MSComm1.Output = "AT+CGSN" + Chr$(13)
Set allflag = Form3.Text3
'Form1.Timer1.Enabled = True

End Sub

Private Sub command4_Click()
Form3.Text4 = " "
Form1.MSComm1.Output = "AT+WDOP" + Chr$(13)
Set allflag = Form3.Text4
'Form1.Timer1.Enabled = True

End Sub

Private Sub Command5_Click()
Form3.Text5 = " "
Form1.MSComm1.Output = "AT+WHWV" + Chr$(13)
Set allflag = Form3.Text5
'Form1.Timer1.Enabled = True

End Sub

