#pragma once

namespace animationCWK2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		String^ GetSourceFilePath()
		{
			return  this->openSourceDialog->FileName;
		}

		String^ GetDestinationFilePath()
		{
			return this->saveFileDialog->FileName;
		}

		boolean GetSimulation1CheckState()
		{
			return this->Simulation1->Checked;
		}

		boolean GetSimulation2CheckState()
		{
			return this->Simulation2->Checked;
		}

		boolean GetSimulation3CheckState()
		{
			return this->Simulation3->Checked;
		}

		boolean GetSimulation4CheckState()
		{
			return this->Simulation4->Checked;
		}

		String^ GetSaveLabelText()
		{
			return this->SaveAsLabel->Text;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ LoadButton;
	private: System::Windows::Forms::Button^ SaveButton;
	protected:

	protected:

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ LoadLabel;
	private: System::Windows::Forms::Label^ SaveAsLabel;
	private: System::Windows::Forms::OpenFileDialog^ openSourceDialog;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog;
	private: System::Windows::Forms::CheckBox^ Simulation1;
	private: System::Windows::Forms::CheckBox^ Simulation2;
	private: System::Windows::Forms::CheckBox^ Simulation3;
	private: System::Windows::Forms::CheckBox^ Simulation4;







	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LoadButton = (gcnew System::Windows::Forms::Button());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->LoadLabel = (gcnew System::Windows::Forms::Label());
			this->SaveAsLabel = (gcnew System::Windows::Forms::Label());
			this->openSourceDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->Simulation1 = (gcnew System::Windows::Forms::CheckBox());
			this->Simulation2 = (gcnew System::Windows::Forms::CheckBox());
			this->Simulation3 = (gcnew System::Windows::Forms::CheckBox());
			this->Simulation4 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// LoadButton
			// 
			this->LoadButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LoadButton->Location = System::Drawing::Point(12, 9);
			this->LoadButton->Name = L"LoadButton";
			this->LoadButton->Size = System::Drawing::Size(136, 48);
			this->LoadButton->TabIndex = 0;
			this->LoadButton->Text = L"Load";
			this->LoadButton->UseVisualStyleBackColor = true;
			this->LoadButton->Click += gcnew System::EventHandler(this, &MyForm::LoadButton_Click);
			// 
			// SaveButton
			// 
			this->SaveButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SaveButton->Location = System::Drawing::Point(12, 83);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(136, 48);
			this->SaveButton->TabIndex = 1;
			this->SaveButton->Text = L"Save as";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &MyForm::SaveButton_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(12, 301);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(622, 48);
			this->button3->TabIndex = 2;
			this->button3->Text = L"PLAY";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::PlayButton_Click);
			// 
			// LoadLabel
			// 
			this->LoadLabel->Location = System::Drawing::Point(155, 9);
			this->LoadLabel->Name = L"LoadLabel";
			this->LoadLabel->Size = System::Drawing::Size(479, 48);
			this->LoadLabel->TabIndex = 3;
			this->LoadLabel->Text = L"Load file path";
			this->LoadLabel->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// SaveAsLabel
			// 
			this->SaveAsLabel->Location = System::Drawing::Point(155, 83);
			this->SaveAsLabel->Name = L"SaveAsLabel";
			this->SaveAsLabel->Size = System::Drawing::Size(479, 48);
			this->SaveAsLabel->TabIndex = 4;
			this->SaveAsLabel->Text = L"Save file path";
			// 
			// openSourceDialog
			// 
			this->openSourceDialog->FileName = L"openSourceDialog";
			this->openSourceDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openSourceDialog_FileOk);
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog_FileOk);
			// 
			// Simulation1
			// 
			this->Simulation1->AutoSize = true;
			this->Simulation1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Simulation1->Location = System::Drawing::Point(16, 156);
			this->Simulation1->Name = L"Simulation1";
			this->Simulation1->Size = System::Drawing::Size(286, 22);
			this->Simulation1->TabIndex = 5;
			this->Simulation1->Text = L"Cloth - Floor Freefall Collision Scenario";
			this->Simulation1->UseVisualStyleBackColor = true;
			this->Simulation1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Simulation1_CheckedChanged);
			// 
			// Simulation2
			// 
			this->Simulation2->AutoSize = true;
			this->Simulation2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Simulation2->Location = System::Drawing::Point(16, 185);
			this->Simulation2->Name = L"Simulation2";
			this->Simulation2->Size = System::Drawing::Size(278, 22);
			this->Simulation2->TabIndex = 6;
			this->Simulation2->Text = L"SS1: Cloth-Sphere and Floor Collision";
			this->Simulation2->UseVisualStyleBackColor = true;
			this->Simulation2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Simulation2_CheckedChanged);
			// 
			// Simulation3
			// 
			this->Simulation3->AutoSize = true;
			this->Simulation3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Simulation3->Location = System::Drawing::Point(16, 214);
			this->Simulation3->Name = L"Simulation3";
			this->Simulation3->Size = System::Drawing::Size(381, 22);
			this->Simulation3->TabIndex = 7;
			this->Simulation3->Text = L"SS2: Free-fall with two adjacent corners fixed in space";
			this->Simulation3->UseVisualStyleBackColor = true;
			this->Simulation3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Simulation3_CheckedChanged);
			// 
			// Simulation4
			// 
			this->Simulation4->AutoSize = true;
			this->Simulation4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Simulation4->Location = System::Drawing::Point(16, 242);
			this->Simulation4->Name = L"Simulation4";
			this->Simulation4->Size = System::Drawing::Size(173, 22);
			this->Simulation4->TabIndex = 8;
			this->Simulation4->Text = L"SS2 with wind blowing";
			this->Simulation4->UseVisualStyleBackColor = true;
			this->Simulation4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Simulation4_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(651, 384);
			this->Controls->Add(this->Simulation4);
			this->Controls->Add(this->Simulation3);
			this->Controls->Add(this->Simulation2);
			this->Controls->Add(this->Simulation1);
			this->Controls->Add(this->SaveAsLabel);
			this->Controls->Add(this->LoadLabel);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->LoadButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		String^ filePath = "";
		saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "3D Object|*.obj";
		saveFileDialog->Title = "Save an .obj file";
		saveFileDialog->ShowDialog();

		if (saveFileDialog->FileName != "")
		{ //if file is not null
			filePath = saveFileDialog->FileName;
			SaveAsLabel->Text = saveFileDialog->FileName;
		}
	}
	private: System::Void PlayButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (openSourceDialog->FileName == L"openSourceDialog")
		{
			MessageBox::Show("NO FILE CHOSEN", "Choose a file before pressing play", MessageBoxButtons::OK);
			return;
		}
		else 
		{
			this->Close();
		}
		
	}
	private: System::Void LoadButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		openSourceDialog = gcnew OpenFileDialog;
		String^ filePath;

		openSourceDialog->InitialDirectory = "./objs";
		openSourceDialog->Filter = "3D Object|*.obj";
		openSourceDialog->Title = "Load .obj file";
		openSourceDialog->FilterIndex = 2;
		openSourceDialog->RestoreDirectory = true;

		if (openSourceDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			filePath = openSourceDialog->FileName;
			LoadLabel->Text = openSourceDialog->FileName;
		}
		MessageBox::Show(filePath, "File at path: " + filePath, MessageBoxButtons::OK);

	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void openSourceDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
private: System::Void Simulation1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->Simulation1->Checked == true)
	{
		this->Simulation2->Checked = false;
		this->Simulation3->Checked = false;
		this->Simulation4->Checked = false;
	}
}
private: System::Void Simulation2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->Simulation2->Checked == true)
	{
		this->Simulation1->Checked = false;
		this->Simulation3->Checked = false;
		this->Simulation4->Checked = false;
	}
}
private: System::Void Simulation3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->Simulation3->Checked == true)
	{
		this->Simulation1->Checked = false;
		this->Simulation2->Checked = false;
		this->Simulation4->Checked = false;
	}
}
private: System::Void Simulation4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	if (this->Simulation4->Checked == true)
	{
		this->Simulation1->Checked = false;
		this->Simulation2->Checked = false;
		this->Simulation3->Checked = false;
	}
}
private: System::Void saveFileDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
}
};
}
