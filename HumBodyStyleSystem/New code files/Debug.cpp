
//**********
// �������
//**********
// �������� ���� - ��� ���������� ������� �� ����, � ������� �� ������� ����� �������.

namespace GOTHIC_ENGINE {


// ����� �������
bool debugMode = false;

// ������� ��������� ������� �� ����� ������� ��� ���,
// � �������� �� ��� �������� ��������� "HumBodyStyleSystem_DebugMode"
void CheckDebugMode()
{
	// �������� ���������
	if (!parser)
		return;
	
	// �������� ����� ������������� ��������� � ��������
	zCPar_Symbol* ps = parser->GetSymbol("HumBodyStyleSystem_DebugMode");

	// ���� ����� � � ��� �������������
	if (ps && (ps->type == zPAR_TYPE_INT && !ps->HasFlag(zPAR_FLAG_CLASSVAR)))
	{
		int value = 0;
		// �������� �������� ����������
		ps->GetValue(value, 0);

		// ���� ������� ��������
		if (value > 0)
			// �������� � � �����
			debugMode = true;
	}
}


//*************************************************************************
// �������, ����������� ����� ������������� ���� � �������� �������� ����
//*************************************************************************
//0x004CD3B0 public: static void __cdecl zCMenu::Startup(void)
static void Menu_Startup();
static CInvoke <void(*)()> pMenu_Startup(0x004CD3B0, Menu_Startup, IVK_AUTO);
static void Menu_Startup()
{
	// �������� ��������
	pMenu_Startup();

	// ��������� ������� �� ����� ������� � ��������
	CheckDebugMode();
}


	
} /* end namespace */