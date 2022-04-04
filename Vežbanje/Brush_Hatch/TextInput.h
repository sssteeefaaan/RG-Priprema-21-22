#pragma once


// TextInput dialog

class TextInput : public CDialogEx
{
	DECLARE_DYNAMIC(TextInput)

public:
	TextInput(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TextInput();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
