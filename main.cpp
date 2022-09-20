#define CURL_STATICLIB
#include "main.h"
#include <urlmon.h>
#include <string>
#include <stdio.h>
#using   <system.drawing.dll>
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <curl\curl.h>

using namespace System;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Windows::Forms;


[STAThread]
void main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    RealnamesautoUpdate::main form;
    Application::Run(% form); 
}

size_t DownloadFile(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

System::Void RealnamesautoUpdate::main::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    if (comboBox1->SelectedIndex == 0)
        textBox1->Text = "https://raw.githubusercontent.com/execut4ble/realnames/master/realnames.txt";

    if (comboBox1->SelectedIndex == 1)
        textBox1->Text = "https://raw.githubusercontent.com/L09k0/realname/agmod/realnamesLogko.txt";

    if (comboBox1->SelectedIndex == 2)
        textBox1->Text = "https://raw.githubusercontent.com/L09k0/realname/agmod/realnamesNurdik.txt";
    
}

System::Void RealnamesautoUpdate::main::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        String^ name = folderBrowserDialog1->SelectedPath;
        textBox2->Text = name;
    }
}

System::Void RealnamesautoUpdate::main::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    char* url;
    //char outfilename[FILENAME_MAX] = "real.txt";
    if (comboBox1->SelectedIndex == 0)
        url = "https://raw.githubusercontent.com/execut4ble/realnames/master/realnames.txt";

    if (comboBox1->SelectedIndex == 1)
        url = "https://raw.githubusercontent.com/L09k0/realname/agmod/realnamesLogko.txt";

    if (comboBox1->SelectedIndex == 2)
        url = "https://raw.githubusercontent.com/L09k0/realname/agmod/realnamesNurdik.txt";

    String^ path_temp = textBox2->Text;
    if (textBox2->Text == " ")
    {
        MessageBox::Show("indicate the path!", "Error!");
    }
    std::string path_temp2 = msclr::interop::marshal_as< std::string >(path_temp);
    std::string path_temp3 = path_temp2 + "realnames.txt";
    const char* cstr = path_temp3.c_str();

    CURL* curl;
    FILE* fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(cstr, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DownloadFile);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        MessageBox::Show("Successful\n\nÓñïåøíî!", "Good!");
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

System::Void RealnamesautoUpdate::main::Exit_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
}

System::Void RealnamesautoUpdate::main::linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
{
    system("start doc\\prog.html");
}
