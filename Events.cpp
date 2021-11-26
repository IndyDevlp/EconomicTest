#include "Registr.h"
#include "Passtest.h"


System::Void TFStudents::Registr::maskedTextBoxFam_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Return)
		maskedTextBoxName->Focus();
}

System::Void TFStudents::Registr::maskedTextBoxName_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Return)
		maskedTextBoxMidName->Focus();
}

System::Void TFStudents::Registr::maskedTextBoxGroup_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Return)
		buttonStartTest->Focus();
}

System::Void TFStudents::Registr::maskedTextBoxMidName_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Return)
		maskedTextBoxGroup->Focus();
}

System::Void TFStudents::Registr::buttonStartTest_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ ErrorMessage;

	if (maskedTextBoxFam->Text != "" &&
		maskedTextBoxName->Text != "" &&
		maskedTextBoxMidName->Text != "" &&
		maskedTextBoxGroup->Text != "" &&
		comboBoxTheme->SelectedItem != nullptr)
	{
		this->Hide();
		Passtest^ FormTest = gcnew Passtest(this);
		FormTest->ShowDialog();
	}
	else
	{
		if (maskedTextBoxFam->Text == "")
			ErrorMessage = ErrorMessage + "- �������\n";

		if (maskedTextBoxName->Text == "")
			ErrorMessage = ErrorMessage + "- ���\n";

		if (maskedTextBoxMidName->Text == "")
			ErrorMessage = ErrorMessage + "- ��������\n";

		if (maskedTextBoxGroup->Text == "")
			ErrorMessage = ErrorMessage + "- ������\n";

		if(comboBoxTheme->SelectedItem == nullptr)
			ErrorMessage = ErrorMessage + "- �� ������� ����";

		MessageBox::Show("�� �� ��������� ��������� ����:\n " + ErrorMessage, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void TFStudents::Registr::comboBoxTheme_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (comboBoxTheme->SelectedIndex == 3)
		comboBoxTheme->SelectedIndex = -1;
}

System::Void TFStudents::Registr::maskedTextBoxFam_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
	if (!(e->KeyChar <= 47 || e->KeyChar >= 58))
	{
		e->Handled = true;
	}
}

System::Void TFStudents::Registr::label1_Click(System::Object^ sender, System::EventArgs^ e)
{
	maskedTextBoxFam->Focus();
}

System::Void TFStudents::Registr::label2_Click(System::Object^ sender, System::EventArgs^ e)
{
	maskedTextBoxName->Focus();
}

System::Void TFStudents::Registr::label3_Click(System::Object^ sender, System::EventArgs^ e)
{
	maskedTextBoxMidName->Focus();
}

System::Void TFStudents::Registr::label4_Click(System::Object^ sender, System::EventArgs^ e)
{
	maskedTextBoxGroup->Focus();
}

System::Void TFStudents::Passtest::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	--timeCounter;
	labelTimer->Text = "�������� ������� - " + (timeCounter / 60).ToString() + " : " + (timeCounter % 60).ToString();

	if (timeCounter == 0)
	{
		StopTest();
	}
}

System::Void TFStudents::Passtest::Passtest_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	mainForm->Close();
}

System::Void TFStudents::Passtest::buttonAnswer_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (Equals(arrayOfAnswers[_QuestionCount++], ((Button^)sender)->Text))
		_RightAnswerCount++;

	RandomQuestion();
}

System::Void TFStudents::Passtest::Passtest_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	System::Windows::Forms::DialogResult result;
	result = MessageBox::Show("�� �������, ��� ������ ���������?", "��������������", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes)
		Application::ExitThread();
	else if (result == System::Windows::Forms::DialogResult::No) e->Cancel = true;
}
