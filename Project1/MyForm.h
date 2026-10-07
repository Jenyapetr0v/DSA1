#pragma once

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::Button^ buttonSort;
	private: System::Windows::Forms::ListBox^ listBoxSteps;
	private: System::Windows::Forms::Label^ labelResult;
	private: System::Windows::Forms::TextBox^ textBoxInput;
	private: System::Windows::Forms::Label^ label1;
	protected:


	protected:

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
			this->buttonSort = (gcnew System::Windows::Forms::Button());
			this->listBoxSteps = (gcnew System::Windows::Forms::ListBox());
			this->labelResult = (gcnew System::Windows::Forms::Label());
			this->textBoxInput = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonSort
			// 
			this->buttonSort->Location = System::Drawing::Point(27, 77);
			this->buttonSort->Name = L"buttonSort";
			this->buttonSort->Size = System::Drawing::Size(117, 23);
			this->buttonSort->TabIndex = 0;
			this->buttonSort->Text = L"Сортувати";
			this->buttonSort->UseVisualStyleBackColor = true;
			this->buttonSort->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// listBoxSteps
			// 
			this->listBoxSteps->FormattingEnabled = true;
			this->listBoxSteps->ItemHeight = 16;
			this->listBoxSteps->Location = System::Drawing::Point(161, 77);
			this->listBoxSteps->Name = L"listBoxSteps";
			this->listBoxSteps->Size = System::Drawing::Size(356, 180);
			this->listBoxSteps->TabIndex = 1;
			// 
			// labelResult
			// 
			this->labelResult->AutoSize = true;
			this->labelResult->Location = System::Drawing::Point(83, 252);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(44, 16);
			this->labelResult->TabIndex = 2;
			this->labelResult->Text = L"label1";
			this->labelResult->Click += gcnew System::EventHandler(this, &MyForm::labelResult_Click);
			// 
			// textBoxInput
			// 
			this->textBoxInput->Location = System::Drawing::Point(133, 40);
			this->textBoxInput->Name = L"textBoxInput";
			this->textBoxInput->Size = System::Drawing::Size(100, 22);
			this->textBoxInput->TabIndex = 3;
			this->textBoxInput->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxInput_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Введіть масив:";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(543, 382);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxInput);
			this->Controls->Add(this->labelResult);
			this->Controls->Add(this->listBoxSteps);
			this->Controls->Add(this->buttonSort);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}


private:
	System::String^ ArrayToString(array<int>^ arr) {
		System::String^ res = "";
		for (int i = 0; i < arr->Length; i++) {
			res += arr[i] + " ";
		}
		return res;
	}

	int CustomCountingSort(array<int>^ A, array<int>^ B, System::Windows::Forms::ListBox^ listBox) {
		int n = A->Length;
		int comparisons = 0;

		for (int i = 0; i < n; i++) {
			B[i] = -1;
		}
		listBox->Items->Add("Етап 1: Масив заповнено '-1': [" + ArrayToString(B) + "]");

		for (int i = 0; i < n; i++) {
			int count = 0;
			for (int j = 0; j < n; j++) {
				comparisons++;
				if (A[j] < A[i]) {
					count++;
				}
			}
			B[count] = A[i];
			listBox->Items->Add("Елемент " + A[i] + " має " + count + " менших. Поточний стан: [" + ArrayToString(B) + "]");
		}

		for (int i = 1; i < n; i++) {
			if (B[i] == -1) {
				B[i] = B[i - 1];
			}
		}
		listBox->Items->Add("Етап 3: Заповнення дублікатів замість '-1'.");

		return comparisons;
	}


private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	listBoxSteps->Items->Clear();

	array<System::String^>^ strElements = textBoxInput->Text->Split(
		gcnew array<wchar_t>{' ', ','}, System::StringSplitOptions::RemoveEmptyEntries);

	if (strElements->Length == 0) {
		MessageBox::Show("Будь ласка, введіть масив!");
		return;
	}

	array<int>^ A = gcnew array<int>(strElements->Length);
	for (int i = 0; i < strElements->Length; i++) {
		A[i] = System::Convert::ToInt32(strElements[i]);
	}

	array<int>^ B = gcnew array<int>(A->Length);

	int comps = CustomCountingSort(A, B, listBoxSteps);

	listBoxSteps->Items->Add("--------------------------------");
	listBoxSteps->Items->Add("ФІНАЛЬНИЙ ВІДСОРТОВАНИЙ МАСИВ: [" + ArrayToString(B) + "]");
	labelResult->Text = "Трудомісткість (кількість порівнянь): " + comps;
}
	private: System::Void labelResult_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBoxInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
