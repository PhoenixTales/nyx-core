
//***************************
// ����� ���������� �������
//***************************
namespace GOTHIC_ENGINE {


// void Mdl_SetHumBodyType(C_NPC npc, string type) - ������������� ������� ����� ������� ���� � ������ ���
int Mdl_SetHumBodyType()
{
	// �������� ��������� �� ������� ������ ������� ��������
	zCParser* par = zCParser::GetParser();

	// �������� �������
	zSTRING type;
	par->GetParameter(type);

	// ����� ������ � ���������
	string sType = type;


	// �������� ��������� �� ���
	oCNpc* pNpc = dynamic_cast<oCNpc*>((zCVob*)parser->GetInstance());

	// ������ ���������
	if (!pNpc)
		return 0;


	// �������� ����� ��������� ���
	int id = pNpc->GetInstance();

	// ----------------------------



	// ��������� ������ ��������� (���� ����������)
	int found_idx = -1;

	// ����������� �� ������� ��������
	for (uint i = 0; i < arr_HumBodyStyles.GetNum(); i++)
	{
		// ���� ������� ��������� � ���������� ���������� ���
		if (arr_HumBodyStyles[i]->inst_id == id)
		{
			// ���������� � �����
			found_idx = i;

			// ������� �� �����
			break;
		}
	}



	// ���� �������� ��� �� �������
	// (���� ������ ������ ��� ������ ��� �� ��������� ��� ���)
	bool bRemove = sType.IsEmpty() || sType.CompareI("NAKED");


	// ���� ��������� � ��� �� ������� � ������ ����� ����� ����
	if (found_idx < 0 && !bRemove)
		// ������ ����� ���������, ����������� �� �������� � ��������� � ������
		arr_HumBodyStyles.Insert(new Hum_BodyStyle(id, Add_HumBodyType(sType)));
	// ��� ���� ��������� � ��� �������, �� � ����� ������� �� �������
	else if (found_idx >= 0 && bRemove)
		// ������� �� �������
		arr_HumBodyStyles.FastDeleteAt(found_idx);
	// ��� ���� ��������� � ��� �������, �� � �� ����� ������� �� �������
	else if (found_idx >= 0 && !bRemove)
		// ������ ������ �������� �����
		arr_HumBodyStyles[found_idx]->style_idx = Add_HumBodyType(sType);

	return 0;
}



// ����������� ����� ���������� �������
void Reg_GameExternals()
{
	// void Mdl_SetHumBodyType(C_NPC npc, string type)
	parser->DefineExternal("Mdl_SetHumBodyType", Mdl_SetHumBodyType, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, 0);
}



} /* end namespace */