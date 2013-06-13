// XML Dialog Box
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x700
#endif
#include <windows.h>
#ifndef WINCE
#include <richedit.h>
#endif
#include <commctrl.h>
#include "xml.h"
#include <string>
#include <vector>
using namespace std;
#include "grid.h"
#include "xdb.h"

#pragma warning(default: 4068)
#pragma warning(default : 4311)
#pragma warning(disable : 4996)
#pragma warning(disable : 4244)

#ifdef _UNICODE
static void VectorStringFromString(vector<wstring>& s,const TCHAR* st,const TCHAR* del)
#else
static void VectorStringFromString(vector<string>& s,const TCHAR* st,const TCHAR* del)
#endif
	{
	Z<TCHAR> it(_tcslen(st) + 100);
	_tcscpy(it,st);
	TCHAR* a0 = it;
	vector<int> qp;
	int vbup = 0;
	for(;;)
		{
		TCHAR* a1 = _tcsstr(a0 + vbup,del);
		vbup = 0;
		if (a1)
			{
			*a1 = 0;
			}
		if (_tcslen(a0))
#ifdef _UNICODE
			s.insert(s.end(),wstring(a0));
#else
			s.insert(s.end(),string(a0));
#endif
		if (!a1)
			break;
		*a1 = del[0];
		a0 = a1 + _tcslen(del);
		}
	}


void XMLDialogEnd(HWND);
void XMLNameWrap(char* n,bool X)
	{
	if (X == false)
		{
		// from '_' to ' '
		for(unsigned int i = 0 ; i < strlen(n) ; i++)
			{
			if (n[i] == '_')
				n[i] = ' ';
			}
		}
	else
		{
		// from ' ' to '_'
		for(unsigned int i = 0 ; i < strlen(n) ; i++)
			{
			if (n[i] == ' ')
				n[i] = '_';
			}
		}
	}


void XMLElementToTree(XMLDialogBoxOptions* x,XMLElement* r,HWND hT,HTREEITEM hP,XMLElement* de)
   {
   int nC = r->GetChildrenNum();
   Z<char> eln(1);
   Z<TCHAR> weln(1);

   int elnb = 0;
   int nV = 0;
	if (r->FindVariableZ("name"))
		{
		elnb = r->FindVariableZ("name")->GetValue(0);
		eln.Resize(elnb + 100);
		weln.Resize(elnb + 100);
		r->FindVariableZ("name",true)->GetValue(eln);
		}
	else
	if (r->FindVariableZ("Name"))
		{
		elnb = r->FindVariableZ("Name")->GetValue(0);
		eln.Resize(elnb + 100);
		weln.Resize(elnb + 100);
		r->FindVariableZ("Name",true)->GetValue(eln);
		}
	else
		{
		elnb = r->GetElementName(0);
		eln.Resize(elnb + 100);
		weln.Resize(elnb + 100);
		r->GetElementName(eln);
		}


	if (de)
		{
		Z<char> fn(1000);
		r->GetElementFullName(fn);
		XMLElement* he = de->GetElementInSection(fn);
		if (he)
			{
			XMLVariable* vt = he->FindVariableZ("__");
			if (vt)
				{
				vt->GetValue(eln);
				}
			}
		}
	XMLNameWrap(eln,false);
	
	// DialogBox2 to test name
	if (x->DP2)
		x->DP2(GetParent(hT),XDB_DISPLAY_ELEMENT,(WPARAM)r,(LPARAM)eln.operator char *());


#ifdef _UNICODE
	MultiByteToWideChar(CP_UTF8,0,eln,-1,weln,elnb + 100);
#else
	strcat(weln,eln);
#endif



   // Root
   TV_INSERTSTRUCT ts = {0};
   ts.hParent = hP;
   ts.hInsertAfter = TVI_LAST	;
   ts.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT;
   ts.item.hItem = hP;
   ts.item.state = 0;
   ts.item.stateMask = 0;
   ts.item.pszText = weln;
   ts.item.cChildren = nC;
   ts.item.lParam = (LPARAM)r;
   HTREEITEM hNewP = TreeView_InsertItem(hT,&ts);

   // Add child elements
   for(int i = 0 ; i < nC ; i++)
      {
		if (!r->GetChildren()[i])
			{
			// Add <Unloaded>
			_stprintf(weln,_T("<Unloaded>"));
		   TV_INSERTSTRUCT ts = {0};
			ts.hParent = hNewP;
			ts.hInsertAfter = TVI_LAST	;
			ts.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT;
			ts.item.hItem = hP;
			ts.item.state = 0;
			ts.item.stateMask = 0;
			ts.item.pszText = weln;
			ts.item.cChildren = nC;
			ts.item.lParam = (LPARAM)r;
			HTREEITEM hNewP2 = TreeView_InsertItem(hT,&ts);
			continue; // unloaded element
			}
      XMLElementToTree(x,r->GetChildren()[i],hT,hNewP,de);
      }

	}

static void UCopy(TCHAR* d,int ms,const char* s)
	{
#ifdef _UNICODE
	MultiByteToWideChar(CP_UTF8,0,s,-1,d,ms);
#else
	strcpy(d,s);
#endif
	}
#ifdef _UNICODE
static void UCopy(char* d,int ms,TCHAR* s)
	{
#ifdef _UNICODE
	WideCharToMultiByte(CP_UTF8,0,s,-1,d,ms,0,0);
#else
	strcpy(d,s);
#endif
	}
#endif

int ListView_FindRemainSize(HWND hL)
	{
	RECT rc;
	GetClientRect(hL,&rc);
	int X = ListView_GetColumnWidth(hL,0);
	return rc.right - X;
	}

static void CreateDialogElements(HWND hh,XMLDialogBoxOptions* o,XMLElement* e)
	{
	// Delete existing
	HWND hL = GetDlgItem(hh,1001);
	HWND hR = GetDlgItem(hh,1002);
	ListView_DeleteAllItems(hL);
	Z<TCHAR> wtmp(1000);
	Z<char> tmp(1000);

	if (!e)
		return;

	SendMessage(hL,LVM_GRIDCLEAR,0,0);

	// DialogBox2 to finish this element
	if (o->DP2)
		o->DP2(hh,XDB_DISPLAY_ELEMENT_BEGIN,(WPARAM)e,0);

	int nV = e->GetVariableNum();
	for(int i = 0 ; i < nV ; i++)
		{
		XMLVariable* v = e->GetVariables()[i];
		v->GetName(tmp);

		if (strncmp(tmp,"__",2) == 0)
			continue; // Bypass that thing

		Z<char> fvar(1000);
		sprintf(fvar,"__%s",tmp.operator char *());
		XMLVariable* fv = e->FindVariableZ(fvar);
		if (fv)
			{
			// Options , so create a combobox
			fv->GetValue(fvar);
			}
		else
			fvar._clear();


		// In case that we have a translation xml, load the name from it
		bool Translated = false;
		if (o->de)
			{
			Z<char> fn(1000);
			e->GetElementFullName(fn);
			XMLElement* he = o->de->GetElementInSection(fn);
			if (he)
				{
				XMLVariable* vt = he->FindVariableZ(tmp);
				if (vt)
					{
					vt->GetValue(tmp);
					}
				}
			}
		XMLNameWrap(tmp,false);
		UCopy(wtmp,1000,tmp);

		
		LV_ITEM lv = {LVIF_TEXT | LVIF_PARAM,i,0,0,0,wtmp,0,0,0};
		lv.lParam = (LPARAM)v;
		int P = ListView_InsertItem(hL,&lv);
		v->GetValue(tmp);
		UCopy(wtmp,1000,tmp);

		if (strlen(fvar))
			{
			// Get stuff
			GRID_DATA_CB cb;
			cb.iI = P;
			cb.iS = 1;
#ifdef _UNICODE
			Z<TCHAR> wfvar(1000);
			UCopy(wfvar,1000,fvar);
			VectorStringFromString(cb.txts,wfvar,_T("|||"));
#else
			VectorStringFromString(cb.txts,fvar,_T("|||"));
#endif
			SendMessage(hL,LVM_GRIDSETCB,0,(LPARAM)&cb);
			}

		e->SetElementParam(i);
		if (o->DP2)
			o->DP2(hh,XDB_DISPLAY_VARIABLE,(WPARAM)v,(LPARAM)wtmp.operator TCHAR *());
		ListView_SetItemText(hL,P,1,wtmp);
		}
	int nC = e->GetCDatasNum();
	if (nC)
		{
		const char* s = e->GetCDatas()[0]->operator const char *();
		int sl = (int)strlen(s);
		Z<TCHAR> ws(sl + 100);
		UCopy(ws,sl + 100,s);

		SetWindowText(hR,ws.operator TCHAR *());
		SendMessage(hh,WM_SIZE,0,0);
		}
	else
		{
		SetWindowText(hR,_T(""));
		SendMessage(hh,WM_SIZE,0,0);
		}

	ShowWindow(hL,SW_HIDE);
	SendMessage(hL, LVM_SETCOLUMNWIDTH, 0, LVSCW_AUTOSIZE);
	SendMessage(hL, LVM_SETCOLUMNWIDTH, 1, ListView_FindRemainSize(hL));
	ShowWindow(hL,SW_SHOW);

	// DialogBox2 to finish this element
	if (o->DP2)
		o->DP2(hh,XDB_DISPLAY_ELEMENT_COMPLETED,(WPARAM)e,0);
	}



static LRESULT CALLBACK XMLDialogBoxProc(HWND hh,UINT mm,WPARAM ww,LPARAM ll)
	{
	XMLDialogBoxOptions* xp = (XMLDialogBoxOptions*)GetWindowLongPtr(hh,GWLP_USERDATA);
	HWND hT = GetDlgItem(hh,1000);
	HWND hL = GetDlgItem(hh,1001);
	HWND hR = GetDlgItem(hh,1002);

	if (xp && xp->DP1)
		{
		int RV = xp->DP1(hh,mm,ww,ll);
		if (RV != 0)
			{
			LONG_PTR lp = GetWindowLongPtr(hh,DWLP_MSGRESULT);
			SetWindowLongPtr(hh,DWLP_MSGRESULT,RV);
			return RV;
			}
		}

	switch(mm)
		{
		case WM_APP + 1:
			{
			// Initialize the entries
			XMLElementToTree(xp,xp->e,hT,TVI_ROOT,xp->de);

			int nB = xp->e->GetElementName(0);
			Z<char> celn(nB + 10);
			Z<TCHAR> eln(nB + 10);
			xp->e->GetElementName(celn);
			XMLNameWrap(celn,false);
#ifdef _UNICODE
			MultiByteToWideChar(CP_UTF8,0,celn,-1,eln,nB + 10);
#else
			strcpy(eln,celn);
#endif
			SetWindowText(hh,eln);
			SendMessage(hT,TVM_EXPAND,TVE_EXPAND,(LPARAM)TreeView_GetRoot(hT));

			if (xp->DP2)
				xp->DP2(hh,XDB_INIT_COMPLETED,0,0);
			break;
			}

		case WM_NOTIFY:
			{
			NMHDR* n = (NMHDR*)ll;
			if (n->hwndFrom == hL && (n->code == LVN_BEGINSUBITEMEDIT || n->code == LVN_BEGINLABELEDIT))
				{
				NMLVDISPINFO* nl = (NMLVDISPINFO*)n;
				if (nl->item.iSubItem == 0)
					{
					SetWindowLongPtr(hh,DWLP_MSGRESULT,TRUE);
					return TRUE; // block editing
					}

				// Check if there is a custom edit
				if (xp->DP2)
					{
					Z<TCHAR> nt(1000);
					
					LV_ITEM lv = {0};
					lv.mask = LVIF_PARAM;
					lv.iItem = nl->item.iItem;
					ListView_GetItem(hL,&lv);
					XMLVariable* v = (XMLVariable*)lv.lParam;

					LRESULT X = xp->DP2(hh,XDB_EDIT_VARIABLE,(WPARAM)v,(LPARAM)nt.operator TCHAR *());
					if (X == 1)
						return TRUE; // no editing, user cancelled
					if (X == 2)
						{
						ListView_SetItemText(hL,nl->item.iItem,nl->item.iSubItem,nt);
						SendMessage(hL, LVM_SETCOLUMNWIDTH, 1, ListView_FindRemainSize(hL));
						return TRUE; // Custom DP edited the variable, must update
						}
					}

				return FALSE;
				}

			if (n->hwndFrom == hL && (n->code == LVN_ENDSUBITEMEDIT))
				{
				SetWindowLongPtr(hh,DWLP_MSGRESULT,TRUE);
				return TRUE; // allow editing
				}

			if (n->hwndFrom == hL && (n->code == LVN_ENDSUBITEMEDITCOMPLETE))
				{
				NMLVDISPINFO* nl = (NMLVDISPINFO*)n;
				if (nl->item.pszText == 0)
					return 0; // nothing changed

				// Item changed
				LV_ITEM lv = {0};
				lv.mask = LVIF_PARAM;
				lv.iItem = nl->item.iItem;
				ListView_GetItem(hL,&lv);
				XMLVariable* v = (XMLVariable*)lv.lParam;
				if (v)
					{
					Z<char> tmp(1000);
					UCopy(tmp,1000,nl->item.pszText);
					v->SetValue(tmp);
					if (xp->DP2)
						xp->DP2(hh,XDB_EDIT_VARIABLE_COMPLETED,(WPARAM)v,(LPARAM)nl->item.pszText);
					}
				return 0;
				}

			if (n->code == TVN_SELCHANGING && n->hwndFrom == hT)
				{
				NMTREEVIEW* nt = (NMTREEVIEW*)n;
				int n = GetWindowTextLength(hR);
				if (!n)
					return 0;
				Z<TCHAR> t(n + 10);
				GetWindowText(hR,t,n + 10);
				Z<char> st(n + 100);
				UCopy(st,n + 100,t);

				HTREEITEM hTR = nt->itemOld.hItem;
            TV_ITEM tv = {0};
            tv.mask = LVIF_PARAM;
            tv.hItem = hTR;
            TreeView_GetItem(hT,&tv);
            XMLElement* el = (XMLElement*)tv.lParam;
				if (el)
					{
					if (el->GetCDatasNum() == 0)
						el->AddCData("",0);
					el->GetCDatas()[0]->SetCData(st);
					}


				return 0;
				}

			if (n->code == TVN_SELCHANGED && n->hwndFrom == hT)
				{
				// Find element
            HTREEITEM hTR = TreeView_GetSelection(hT);
            if (!hTR)
               return 0;

            TV_ITEM tv = {0};
            tv.mask = LVIF_PARAM;
            tv.hItem = hTR;
            TreeView_GetItem(hT,&tv);

            XMLElement* el = (XMLElement*)tv.lParam;
				CreateDialogElements(hh,xp,el);

				return 0;
				}

			break;
			}

		case WM_APP + 2:
			{
			return (LONG_PTR)xp;
			break;
			}

		case WM_SIZE:
			{
			if (xp->Type != 2)
				break;

			RECT rC = {0};
			GetClientRect(hh,&rC);

			//float mh = 0.95f;
			float mh = 1.0f;
			float mh2 = mh;

			if (GetWindowTextLength(hR))
				mh2 = 0.5f;

			SetWindowPos(hT,0,0,0,rC.right*0.2f,rC.bottom*mh,SWP_SHOWWINDOW);
			SetWindowPos(hL,0,rC.right*0.2f,0,rC.right*0.8f,rC.bottom*mh2,SWP_SHOWWINDOW);
			SetWindowPos(hR,0,rC.right*0.2f,rC.bottom*mh2,rC.right*0.8f,rC.bottom*(1 - mh2),SWP_SHOWWINDOW);
			break;
			}

		case WM_CREATE:
			{
			CREATESTRUCT* xC = (LPCREATESTRUCT)ll;
			xp = (XMLDialogBoxOptions*)xC->lpCreateParams;
			SetWindowLongPtr(hh,GWLP_USERDATA,(LONG_PTR)xp);
			
			// We have to create our windows
			hT = CreateWindowEx(0,WC_TREEVIEW,_T(""),WS_CHILD | WS_BORDER | WS_VISIBLE | TVS_FULLROWSELECT | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,0,0,100,100,hh,(HMENU)1000,GetModuleHandle(0),0);
			hL = CreateWindowEx(0,_T("grid"),_T(""),WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_REPORT,0,0,100,100,hh,(HMENU)1001,GetModuleHandle(0),0);
			hR = CreateWindowEx(0,RICHEDIT_CLASS,_T(""),WS_CHILD | WS_BORDER | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN,0,0,100,100,hh,(HMENU)1002,GetModuleHandle(0),0);

			int KX = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;
         SendMessage(hL, LVM_FIRST + 54,KX,KX);

			// LV columns
         LV_COLUMN lv0 = {LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH,0,70,_T("")};
   	   ListView_InsertColumn(hL,0,&lv0);

         LV_COLUMN lv1 = {LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH,0,100,_T("")};
  	      ListView_InsertColumn(hL,1,&lv1);

			if (xp->DP1)
				xp->DP1(hh,mm,ww,ll);
			SendMessage(hh,WM_APP + 1,0,0);
			break;
			}

		case WM_INITDIALOG:
			{
			xp = (XMLDialogBoxOptions*)ll;
			SetWindowLongPtr(hh,GWLP_USERDATA,(LONG_PTR)xp);

			SendMessage(hh,WM_APP + 1,0,0);
			break;
			}

		case WM_CLOSE:
			{
			// Last TreeView Save
			int n = GetWindowTextLength(hR);
			if (n)
				{
				Z<TCHAR> t(n + 10);
				GetWindowText(hR,t,n + 10);
				Z<char> st(n + 100);
				UCopy(st,n + 100,t);

				HTREEITEM hTR = TreeView_GetSelection(hT);
            TV_ITEM tv = {0};
            tv.mask = LVIF_PARAM;
            tv.hItem = hTR;
            TreeView_GetItem(hT,&tv);
            XMLElement* el = (XMLElement*)tv.lParam;
				if (el)
					{
					if (el->GetCDatasNum() == 0)
						el->AddCData("",0);
					el->GetCDatas()[0]->SetCData(st);
					}
				}

			if (xp->Type == 1)
				EndDialog(hh,IDCANCEL);
			else
				{
				DestroyWindow(hh);
				}
			break;
			}

		case WM_DESTROY:
			{
			if (xp)
				{
				XMLDialogEnd(hh);
				}
			break;
			}

		}

	if (xp && xp->Type == 1)
		return FALSE;
	return DefWindowProc(hh,mm,ww,ll);
	}

INT_PTR XMLDialogBox(HWND hP,XMLElement* e,bool UP,HINSTANCE cI,TCHAR* tem,bool M,DLGPROC DP1,DLGPROC DP2,LPARAM ll,XMLElement* de)
	{
	/*
		Creates a XML Dialog Box which would describe items and variables
		// underscores are converted to spaces

	*/

	
	int rV = 0;
	HINSTANCE hI = GetModuleHandle(0);

	Z<char> tmp1(1000);
	Z<TCHAR> tmp2(1000);
	HWND hX = 0;

	XMLDialogBoxOptions* xp = new XMLDialogBoxOptions;
	xp->e = e;
	xp->de = de;
	xp->DP1 = DP1;
	xp->DP2 = DP2;
	xp->P = UP;
	xp->lp = ll;

	if (cI == 0)
		{
		xp->Type = 2;

		// Create the Window
	   WNDCLASS wC = { 0 };
	   wC.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wC.lpfnWndProc = XMLDialogBoxProc;
	   wC.hInstance = hI;
	   wC.hIcon = LoadIcon(0,IDC_ARROW);
	   wC.hCursor = LoadCursor(0, IDC_ARROW);
	   wC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	   wC.lpszClassName = _T("XML_XDB_CLASS");
		RegisterClass(&wC);

	
		hX = CreateWindowEx(0,_T("XML_XDB_CLASS"),tmp2,WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,hP,0,hI,(void*)xp);
		}
	else
		{
		if (M)
			{
			xp->Type = 1;
			rV = DialogBoxParam(cI,tem,hP,(DLGPROC)XMLDialogBoxProc,(LPARAM)xp);
			}
		else
			{
			xp->Type = 0;
			hX = CreateDialogParam(cI,tem,hP,(DLGPROC)XMLDialogBoxProc,(LPARAM)xp);
			}
		}


	if (cI && M) // modal dlg
		{
		// free structure that our dialog/window proc has created
		if (xp)
			delete xp;
		xp = 0;
		return rV; // Modal Dialog Box result
		}

	// Modeless, return HWND then free later
	return (INT_PTR)hX;
	}

void XMLDialogEnd(HWND hh)
	{
	// free structure that our dialog/window proc has created
	XMLDialogBoxOptions* xp = (XMLDialogBoxOptions*)GetWindowLongPtr(hh,GWLP_USERDATA);
	if (xp)
		delete xp;
	xp = 0;
	SetWindowLongPtr(hh,GWLP_USERDATA,0);

	// Unregister Class
//	UnregisterClass(_T("XML_XDB_CLASS"),hI);
	}