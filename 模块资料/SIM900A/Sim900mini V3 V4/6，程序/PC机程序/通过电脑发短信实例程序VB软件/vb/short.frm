VERSION 5.00
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "����"
   ClientHeight    =   4650
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4380
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4650
   ScaleWidth      =   4380
   StartUpPosition =   3  '����ȱʡ
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   360
      Top             =   3000
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   360
      Top             =   2400
   End
   Begin VB.CommandButton Command2 
      Cancel          =   -1  'True
      Caption         =   "�رմ���"
      Height          =   375
      Left            =   3120
      TabIndex        =   5
      Top             =   3720
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "����"
      Height          =   375
      Left            =   1560
      TabIndex        =   4
      Top             =   3720
      Width           =   855
   End
   Begin VB.TextBox Text1 
      Height          =   1575
      Left            =   1560
      TabIndex        =   3
      Top             =   1920
      Width           =   2415
   End
   Begin VB.ComboBox Combo1 
      Height          =   300
      Left            =   1560
      Sorted          =   -1  'True
      TabIndex        =   2
      Top             =   1320
      Width           =   2415
   End
   Begin VB.OptionButton Option2 
      Caption         =   "��������"
      Height          =   375
      Left            =   2280
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   360
      Width           =   1335
   End
   Begin VB.OptionButton Option1 
      Caption         =   "����Ӣ��"
      Height          =   375
      Left            =   480
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   360
      Value           =   -1  'True
      Width           =   1335
   End
   Begin VB.Line Line3 
      X1              =   2760
      X2              =   2760
      Y1              =   2520
      Y2              =   2640
   End
   Begin VB.Line Line2 
      X1              =   1560
      X2              =   2760
      Y1              =   2040
      Y2              =   2520
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      BackColor       =   &H8000000D&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "��Ϣ����"
      ForeColor       =   &H8000000E&
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   1920
      Width           =   975
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      BackColor       =   &H8000000D&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Ŀ�����"
      ForeColor       =   &H8000000E&
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   1320
      Width           =   975
   End
   Begin VB.Line Line1 
      X1              =   240
      X2              =   4080
      Y1              =   1080
      Y2              =   1080
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim tex As Variant
Dim shortflag As Integer '��־���͵�����
Dim shortdial As String '���ź���
Dim shortdialhex As String
Dim shorttext As String '��������
Dim shorttexthex As String 'ʮ�����ƶ�������
Dim shorttextlen As String '���ų���
Dim shorttextlenhex As String
Dim time As Boolean
Private Sub Combo1_Change()
shortdial = Combo1.text
'MsgBox (dial)
End Sub
Private Sub Combo1_Click()
shortdialhex = ""
Dim b, i As Integer
Dim cin, c1, c2, cout As String
shortdial = Combo1.text
b = Len(Combo1.text)
'MsgBox "b = " & (b Mod 2)
For i = 1 To b
    If (i Mod 2 = 0) Then
        c = Mid(shortdial, i - 1, 2)
        c1 = Left(c, 1)
        c2 = Right(c, 1)
        cout = c2 & c1
        shortdialhex = shortdialhex & cout
    'MsgBox "shortdialhex = " & shortdialhex
    End If
Next
shortdialhex = shortdialhex & "F" & Right(shortdial, 1)
'MsgBox "combo1.click = " & shortdial
End Sub
Private Sub Command1_Click()
Dim shortdiall, shortdialr As String
Dim comp1 As Integer
Dim comp2 As Integer

Dim test As Long
test = 0

shortdiall = "13000000000"
shortdialr = "13999999999"
comp1 = StrComp(shortdial, shortdiall)
comp2 = StrComp(shortdialr, shortdial)

If comp1 + comp2 <= 1 Then MsgBox "�����Ŀ������д�������������"
Dim i As Integer
Dim k As Boolean
k = False
For i = 0 To Combo1.ListCount - 1
    If Combo1.List(i) = shortdial Then k = True
Next
If k = False Then Combo1.AddItem (shortdial) '���Ϸ��ĺ��뱣��

shortdialhex = "" '����16���ƺ���
Dim b, ib As Integer
Dim cin, c1, c2, cout As String
shortdial = Combo1.text
b = Len(Combo1.text)
'MsgBox "b = " & (b Mod 2)
For ib = 1 To b
    If (ib Mod 2 = 0) Then
        c = Mid(shortdial, ib - 1, 2)
        c1 = Left(c, 1)
        c2 = Right(c, 1)
        cout = c2 & c1
        shortdialhex = shortdialhex & cout
    'MsgBox "shortdialhex = " & shortdialhex
    End If
Next
shortdialhex = shortdialhex & "F" & Right(shortdial, 1)
    
Dim ii, kk, jj As Integer '����Ҫ���͵��ַ�
Dim aa, bb, cc As String
shorttext = Text1.text
shorttexthex = ""
ii = Len(Text1.text)
kk = 0
For jj = 1 To ii
  aa = Mid(shorttext, jj, 1) '��ȡһ���ַ�
  bb = AscW(aa) '�������
  cc = Hex(bb) '���16����
  If bb < 128 And bb > 0 Then
    kk = kk + 2
    cc = "00" & cc
  Else
      kk = kk + 2
  End If
  shorttexthex = shorttexthex & cc
  'MsgBox "cc=" & cc
Next jj

If kk < 15 Then '����Ҫ�����ı��ĳ���
  shorttextlenhex = "0" + CStr(Hex(kk))
  Else
    If i < 70 Then
      shorttextlenhex = CStr(Hex(kk))
      Else
      shorttextlenhex = "8C"
    End If
End If
shorttextlen = kk
time = False

Select Case shortflag '���Ͷ���

    Case 1
        Form1.MSComm1.Output = "AT+CMGS=" & shortdial & Chr$(13)
        Timer1.Enabled = True
      
        
        'Form1.MSComm1.Output = shorttext & Chr$(26)
        'allflag1 = False
    Case 2
       'MsgBox "shorttextlen=" & shorttextlen
      'MsgBox "shorttextlenhex=" & shorttextlenhex
       'MsgBox "shortdialhex=" & shortdialhex
       Form1.MSComm1.Output = "AT+CMGS=" & (shorttextlen + 15) & Chr$(13)
       Timer2.Enabled = True
       
        'Form1.MSComm1.Output = "0011000D9168" & shortdialhex & "0008A7" & shorttextlenhex & shorttexthex & Chr$(26)
    
       
End Select
    
'MsgBox "shorttext = " & shorttext
Combo1.text = ""
'Text1.Text = ""
'shortdialhex = ""
'shorttexthex = ""


End Sub

Private Sub Command2_Click()
Unload Me
End Sub

Private Sub Form_Load()
shortflag = 1
Option1.Value = True
Form1.MSComm1.Output = "AT+CMGF=1" + Chr$(13)
End Sub

Private Sub Option1_Click()
Option1.Value = True
shortflag = 1
Form1.MSComm1.Output = "AT+CMGF=1" + Chr$(13)
End Sub

Private Sub Option2_Click()
Option2.Value = True
shortflag = 2
Form1.MSComm1.Output = "AT+CMGF=0" + Chr$(13)
End Sub

Private Sub Text1_Change()
'shorttext = Text1.Text
Dim a As String
a = Right(Text1.text, 1)
If a <> "" Then
'MsgBox "a= " & a
    b = AscW(a) '����Ӣ�ģ���������������
    If b > 128 Or b < 20 Then
        If shortflag = 1 Then SendKeys "{BACKSPACE}"
        'MsgBox "b= " & b
    End If
End If

End Sub

Private Sub Timer1_Timer()
Timer1.Enabled = False
'time = True
'MsgBox "shorttext is->" & shorttext
Form1.MSComm1.Output = Text1.text & Chr$(26)
shorttext = ""
Text1.text = ""
End Sub

Private Sub Timer2_Timer()
Timer2.Enabled = False
Form1.MSComm1.Output = "0011000D9168" & shortdialhex & "0008A7" & shorttextlenhex & shorttexthex & Chr$(26)
shortdialhex = ""
shorttexthex = ""
Text1.text = ""
End Sub
