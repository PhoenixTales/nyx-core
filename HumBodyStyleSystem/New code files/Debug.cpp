
//**********
// Отладка
//**********
// Основная цель - это подкрасить красным те меши, у которых не хватает новых текстур.

namespace GOTHIC_ENGINE {


// режим отладки
bool debugMode = false;

// Функция проверяет включён ли режим отладки или нет,
// в скриптах за это отвечает константа "HumBodyStyleSystem_DebugMode"
void CheckDebugMode()
{
	// защищаем указатель
	if (!parser)
		return;
	
	// пытаемся найти целочисленную константу в скриптах
	zCPar_Symbol* ps = parser->GetSymbol("HumBodyStyleSystem_DebugMode");

	// если нашли и её тип соответствует
	if (ps && (ps->type == zPAR_TYPE_INT && !ps->HasFlag(zPAR_FLAG_CLASSVAR)))
	{
		int value = 0;
		// получаем значение переменной
		ps->GetValue(value, 0);

		// если отладка включена
		if (value > 0)
			// включаем её и здесь
			debugMode = true;
	}
}


//*************************************************************************
// Событие, возникающее после инициализации игры и загрузки главного меню
//*************************************************************************
//0x004CD3B0 public: static void __cdecl zCMenu::Startup(void)
static void Menu_Startup();
static CInvoke <void(*)()> pMenu_Startup(0x004CD3B0, Menu_Startup, IVK_AUTO);
static void Menu_Startup()
{
	// вызываем оригинал
	pMenu_Startup();

	// проверяем включён ли режим отладки в скриптах
	CheckDebugMode();
}


	
} /* end namespace */