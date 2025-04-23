#pragma once
#include "Simulador.h"
#include <msclr/marshal_cppstd.h>

namespace SimuladorProcesosGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form {
	public:
		Form1(void) {
			InitializeComponent();
		}

	protected:
		~Form1() {
			if (components) {
				delete components;
			}
		}

	private:
		System::Windows::Forms::DataGridView^ dgvProcesos;
		System::Windows::Forms::ComboBox^ cbAlgoritmo;
		System::Windows::Forms::TextBox^ txtQuantum;
		System::Windows::Forms::Button^ btnSimular;
		System::Windows::Forms::TextBox^ txtGantt;
		System::Windows::Forms::Label^ lblQuantum;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->dgvProcesos = (gcnew System::Windows::Forms::DataGridView());
			this->cbAlgoritmo = (gcnew System::Windows::Forms::ComboBox());
			this->txtQuantum = (gcnew System::Windows::Forms::TextBox());
			this->btnSimular = (gcnew System::Windows::Forms::Button());
			this->txtGantt = (gcnew System::Windows::Forms::TextBox());
			this->lblQuantum = (gcnew System::Windows::Forms::Label());

			// 
			// dgvProcesos
			// 
			this->dgvProcesos->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvProcesos->Location = System::Drawing::Point(12, 12);
			this->dgvProcesos->Name = L"dgvProcesos";
			this->dgvProcesos->Size = System::Drawing::Size(400, 200);
			this->dgvProcesos->AllowUserToAddRows = true;
			this->dgvProcesos->Columns->Add("ID", "ID");
			this->dgvProcesos->Columns->Add("Llegada", "Llegada");
			this->dgvProcesos->Columns->Add("Rafaga", "Ráfaga");

			// 
			// cbAlgoritmo
			// 
			this->cbAlgoritmo->DropDownStyle = ComboBoxStyle::DropDownList;
			this->cbAlgoritmo->Items->AddRange(gcnew array<Object^> { "FCFS", "SJF", "Round Robin" });
			this->cbAlgoritmo->Location = System::Drawing::Point(430, 12);
			this->cbAlgoritmo->Name = L"cbAlgoritmo";
			this->cbAlgoritmo->Size = System::Drawing::Size(150, 21);

			// 
			// txtQuantum
			// 
			this->txtQuantum->Location = System::Drawing::Point(430, 60);
			this->txtQuantum->Name = L"txtQuantum";
			this->txtQuantum->Size = System::Drawing::Size(150, 20);

			// 
			// lblQuantum
			// 
			this->lblQuantum->Location = System::Drawing::Point(430, 40);
			this->lblQuantum->Text = L"Quantum (para RR)";

			// 
			// btnSimular
			// 
			this->btnSimular->Location = System::Drawing::Point(430, 100);
			this->btnSimular->Name = L"btnSimular";
			this->btnSimular->Size = System::Drawing::Size(150, 30);
			this->btnSimular->Text = L"Simular";
			this->btnSimular->Click += gcnew System::EventHandler(this, &Form1::btnSimular_Click);

			// 
			// txtGantt
			// 
			this->txtGantt->Location = System::Drawing::Point(12, 230);
			this->txtGantt->Multiline = true;
			this->txtGantt->Name = L"txtGantt";
			this->txtGantt->Size = System::Drawing::Size(568, 80);
			this->txtGantt->ReadOnly = true;

			// 
			// Form1
			// 
			this->ClientSize = System::Drawing::Size(600, 330);
			this->Controls->Add(this->dgvProcesos);
			this->Controls->Add(this->cbAlgoritmo);
			this->Controls->Add(this->txtQuantum);
			this->Controls->Add(this->lblQuantum);
			this->Controls->Add(this->btnSimular);
			this->Controls->Add(this->txtGantt);
			this->Text = L"Simulador de Planificación de Procesos";
		}
#pragma endregion

	private: System::Void btnSimular_Click(System::Object^ sender, System::EventArgs^ e) {
		std::vector<Proceso> lista;

		for each (DataGridViewRow ^ row in dgvProcesos->Rows) {
			if (row->IsNewRow) continue;
			if (row->Cells[0]->Value == nullptr) continue;

			Proceso p;
			p.id = Convert::ToInt32(row->Cells[0]->Value);
			p.llegada = Convert::ToInt32(row->Cells[1]->Value);
			p.rafaga = Convert::ToInt32(row->Cells[2]->Value);
			lista.push_back(p);
		}

		std::string algoritmo = msclr::interop::marshal_as<std::string>(cbAlgoritmo->SelectedItem->ToString());

		if (algoritmo == "FCFS") {
			Simulador::FCFS(lista);
		}
		else if (algoritmo == "SJF") {
			Simulador::SJF(lista);
		}
		else if (algoritmo == "Round Robin") {
			int quantum = Convert::ToInt32(txtQuantum->Text);
			Simulador::RoundRobin(lista, quantum);
		}

		String^ gantt = "";
		for (const auto& p : lista) {
			gantt += "P" + p.id + " [" + p.inicio + "-" + p.fin + "]  ";
		}
		txtGantt->Text = gantt;
	}
	};
}

