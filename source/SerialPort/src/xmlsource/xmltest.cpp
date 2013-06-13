// 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "xml.h"

int main()
 {
 OleInitialize(0);
 char* f1 = "http://www.turboirc.com/xml/sample1.xml";
 char* f2 = ".\\sample2.xml";
 XMLElement * root;

 XML* x = 0;

 // Load from file or url
 FILE* fp = fopen(f1,"rb");
 if (fp)
	 {
	 // Load from file
	 fclose(fp);
	 x = new XML(f1);
	 }
 else
	 {
	 // Load from url
	 x = new XML(f1,XML_LOAD_MODE_URL);
	 }

 // Parse status check
 int iPS = x->ParseStatus(); // 0 OK , 1 Header warning (not fatal) , 2 Error in parse (fatal)
 bool iTT = x->IntegrityTest(); // TRUE OK
 if (iPS == 2 || iTT == false)
	 {
	 fprintf(stderr,"Error: XML file %s is corrupt (or not a XML file).\r\n\r\n",f1);
	 delete x;
	 return 0;
 }

 root = x->GetRootElement()->GetChildren()[0];

 char y[100];
 //x->GetRootElement()->GetChildren()[0]->FindVariableZ( "v" )->GetValue( y );
 int iii = x->GetRootElement()->GetChildrenNum();

 // Sample export to stdout
 x->Export(stdout,XML_SAVE_MODE_ZERO);


 // Sample XML functions
 fprintf(stdout,"\r\n\r\n---------- XML test ----------\r\n");
 XML_VERSION_INFO xI = {0};
 x->Version(&xI);
 fprintf(stdout,"XML version: %u.%u (%s)\r\n",xI.VersionHigh,xI.VersionLow,xI.RDate);
 int m1 = x->MemoryUsage();
 x->CompressMemory();
 int m2 = x->MemoryUsage();
 fprintf(stdout,"Memory used before/after compression: %u / %u bytes.\r\n",m1,m2);
 fprintf(stdout,"XML header: %s\r\n",x->GetHeader()->operator const char *());

 // Sample XMLElement functions
 fprintf(stdout,"\r\n\r\n---------- XMLElement test ----------\r\n");
 XMLElement* r = x->GetRootElement();
 int nC = r->GetChildrenNum();
 fprintf(stdout,"Root element has %u children.\r\n",nC);
 for(int i = 0 ; i < nC ; i++)
	 {
	 XMLElement* ch = r->GetChildren()[i];
	 int nV = ch->GetVariableNum();
	 int nMaxElName = ch->GetElementName(0);
	 char* n = new char[nMaxElName + 1];
	 ch->GetElementName(n);

	 fprintf(stdout,"\t Child %u: Variables: %u , Name: %s\r\n",i,nV,n);
	 delete[] n;
	 }
 // Add a children to the end
 r->AddElement(new XMLElement(r,(char*)"<testel x=\"1\" />"));

 // Find this element by name
 XMLElement* el = r->FindElementZ("testel");
 if (!el)
	 fprintf(stderr,"Error, element not found!\r\n");
 else
	 {
	 // Add some variables
	 el->AddVariable(new XMLVariable("somename","somevalue"));
	 // Note that the new XMLVariable we added is now owned by el

	 // Export only this element
	 el->Export(stdout,1,XML_SAVE_MODE_ZERO); // this prints <testel somename="somevalue"/>
	 }

 // Find an element that may not exist, get its variable X that may not exist, get 
 // a default value of 0
 int v = r->FindElementZ("elx",true)->FindVariableZ("varx",true)->GetValueInt();
 // Set it to 5, set some more
 r->FindElementZ("elx",true)->FindVariableZ("varx",true)->SetValueInt(5);
 r->FindElementZ("elx",true)->FindVariableZ("varx2",true)->SetValueInt(10);
 // Printout it
 // This would print: <elx varx="5" varx2="10"/>
 r->FindElementZ("elx",true)->Export(stdout,1,XML_SAVE_MODE_ZERO);

 // Remove the var we just added
 int ix = r->FindElement("elx");
 if (ix != -1)
	 r->RemoveVariable(ix);

 // Other XMLElement functions
 r->Copy(); // Copy entire thing to windows clipboard

 XMLElement* nP = XML::Paste();
 if (nP)
	 {
	 fprintf(stdout,"Successfully copy/paste from clipboard.\r\n");
	 delete nP; // This nP is not owned by x, so we must delete it!
	 }

 // Get a duplicate
 XMLElement* dup = r->Duplicate();
 if (dup)
	 delete dup;

 // Add a comment to the root element
 int nComments = r->AddComment(new XMLComment(0,0,"Nice comment"),0); 

 // Add same comment to the header
 x->GetHeader()->AddComment(x->GetRootElement()->GetComments()[nComments - 1]->Duplicate(),0);

 // Use XMLSetString, XMLSetBinaryData
 XMLSetString("El1\\El2\\El3","var1","x",0,x);

 RECT rc = {0};
 GetWindowRect(GetDesktopWindow(),&rc);
 XMLSetBinaryData("El1\\El2\\El3","var2",(char*)&rc,sizeof(rc),0,x);

 // Get again
 RECT rc2 = {0};
 XMLGetBinaryData("El1\\El2\\El3","var2",(char*)&rc2,(char*)&rc2,sizeof(rc2),0,x);
 if (memcmp(&rc,&rc2,sizeof(rc)) != 0)
	 fprintf(stderr,"Error in binary data transfer!\r\n");
 else
	 fprintf(stdout,"Binary data transfer OK!\r\n");

 // Import database in cdrom.mdb
 // Careful; not tested with ACCESS 2007
 /*IMPORTDBPARAMS dbp = {0};
 char f[300] = {0};
 GetCurrentDirectory(300,f);
 strcat(f,"\\cdrom.mdb");
 dbp.dbname = f;
 dbp.nTables = 1;
 dbp.provstr = 0; // use default
 IMPORTDBTABLEDATA tbl = {0};
 strcpy(tbl.name,"Collection"); // Table name in MDB
 strcpy(tbl.itemname,"v");  // Default name for out elements
 tbl.nVariables = 4; // ID , CD , Name , Comments
 char* v1[] = {"ID","CD","Name","Comments"};
 char* v2[] = {"ID","CD","Name","Comments"};
 tbl.Variables = v1;
 tbl.ReplaceVariables = v2; // In case we want different name
 dbp.Tables = &tbl;
 XMLElement* d = 0;
 d = XML::ImportDB(&dbp); 
 if (d && d->IntegrityTest())
	 {
	 d->Export(stdout,1,0);
	 delete d;
	 }
*/

 // XML object save
 // Manipulate export format
 XMLEXPORTFORMAT xf = {0};
 xf.UseSpace = true;
 xf.nId = 2;
 x->SetExportFormatting(&xf);
 if (x->Save(f2) == 1)
	fprintf(stdout,"%s saved.\r\n",f2);

 // XML object bye bye
 delete x;
 }