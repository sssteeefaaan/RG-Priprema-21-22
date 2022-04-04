// TextInput.cpp : implementation file
//

#include "pch.h"
#include "Brush_Hatch.h"
#include "TextInput.h"
#include "afxdialogex.h"


// TextInput dialog

IMPLEMENT_DYNAMIC(TextInput, CDialogEx)

TextInput::TextInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

TextInput::~TextInput()
{
}

void TextInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TextInput, CDialogEx)
END_MESSAGE_MAP()


// TextInput message handlers
