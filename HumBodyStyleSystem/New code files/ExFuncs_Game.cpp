
//***************************
// Новые скриптовые функции
//***************************
namespace GOTHIC_ENGINE {


// void Mdl_SetHumBodyType(C_NPC npc, string type) - устанавливает префикс стиля текстур тела и головы НПС
int Mdl_SetHumBodyType()
{
	// получаем указатель на текущий парсер игровых скриптов
	zCParser* par = zCParser::GetParser();

	// получаем префикс
	zSTRING type;
	par->GetParameter(type);

	// копия строки с префиксом
	string sType = type;


	// получаем указатель на НПС
	oCNpc* pNpc = dynamic_cast<oCNpc*>((zCVob*)parser->GetInstance());

	// защита указателя
	if (!pNpc)
		return 0;


	// получаем номер инстанции НПС
	int id = pNpc->GetInstance();

	// ----------------------------



	// найденный индекс структуры (пока неизвестен)
	int found_idx = -1;

	// пробегаемся по массиву структур
	for (uint i = 0; i < arr_HumBodyStyles.GetNum(); i++)
	{
		// если нашлась структура с подходящей инстанцией НПС
		if (arr_HumBodyStyles[i]->inst_id == id)
		{
			// запоминаем её идекс
			found_idx = i;

			// выходим из цикла
			break;
		}
	}



	// Флаг удаления НПС из массива
	// (если строка пустая или выбран тип по умолчанию для НПС)
	bool bRemove = sType.IsEmpty() || sType.CompareI("NAKED");


	// если структура с НПС не найдена и задаётя новый стиль тела
	if (found_idx < 0 && !bRemove)
		// создаём новую структуру, присваиваем ей значения и вставляем в массив
		arr_HumBodyStyles.Insert(new Hum_BodyStyle(id, Add_HumBodyType(sType)));
	// или если структура с НПС найдена, но её нужно удалить из массива
	else if (found_idx >= 0 && bRemove)
		// удаляем по индексу
		arr_HumBodyStyles.FastDeleteAt(found_idx);
	// или если структура с НПС найдена, но её НЕ нужно удалять из массива
	else if (found_idx >= 0 && !bRemove)
		// просто меняем значение стиля
		arr_HumBodyStyles[found_idx]->style_idx = Add_HumBodyType(sType);

	return 0;
}



// Регистрация новых скриптовых функций
void Reg_GameExternals()
{
	// void Mdl_SetHumBodyType(C_NPC npc, string type)
	parser->DefineExternal("Mdl_SetHumBodyType", Mdl_SetHumBodyType, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, 0);
}



} /* end namespace */