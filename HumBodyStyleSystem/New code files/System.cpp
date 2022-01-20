

//********************************************************
// Система подстановки новых текстур для тел и голов НПС
//********************************************************
namespace GOTHIC_ENGINE {

// режим отладки
extern bool debugMode;

// массив ненайденных текстур
Array<string> arr_NotFoundTextures;

// Выводит в консоль Юнион отсутствующие текстуры
// (каждое название выводится однократно, а не постоянно)
bool Print_TexNotFound(const string& texName, bool IsBodyTex, oCNpc* pNpc)
{
	// Если такое название уже есть в массиве отсутствующих текстур
	if (arr_NotFoundTextures.HasEqual(texName))
		// выходим, т.к. она уже есть в консоли
		return false;

	// если текстура не найдена в массиве, то добавляем её
	arr_NotFoundTextures.Insert(texName);

	// текст сообщения
	string msg = "";

	// выбираем принадлежность текстуры
	if (IsBodyTex)
		msg = "Body";
	else
		msg = "Head";

	// формируем полный текст сообщения
	msg = msg + " texture '" + texName + A "' not found! (Npc: " + A pNpc->GetInstanceName() + A ")";

	// и выводим его в консоль
	dllPrint(msg);

	// успешный вывод
	return true;
}

//------------------------


// массив текстовых префиксов НПС (Miner, Psionic, Mage, CookSmith...)
Array<string> arr_HumTypes;

// Добавляет новый префикс
// typeName - текстовое название префикса
int Add_HumBodyType(const string& typeName)
{
	// пробегаемся по массиву префиксов
	for (uint i = 0; i < arr_HumTypes.GetNum(); i++)
	{
		// если такой элемент уже существует
		if (arr_HumTypes[i].CompareI(typeName))
			// возвращаем его индекс
			return i;
	}

	// если элемент так и не найден
	// добавляем новый элемент в массив
	arr_HumTypes.InsertEnd(typeName);

	// поднимаем символы новой строки в ВЕРХНИЙ регистр
	arr_HumTypes.GetLast().Upper();

	// и возвращаем индекс префикса
	return arr_HumTypes.GetNum() - 1;
}

// ---------------------------------


// структура с инстанцией НПС и ссылкой на его текстовый префикс
struct Hum_BodyStyle
{
	int	inst_id;	// номер инстанции НПС
	int	style_idx;	// индекс префикса (для текстуры тела и головы)

	// Конструктор
	// (id - номер инстанции НПС, idx - индекс префикса в общем массиве префиксов)
	Hum_BodyStyle( int id, int idx )
	{
		inst_id = id;
		style_idx = idx;
	}
};

// общий массив структур с инстанциями и ссылками на их префиксы
Array<Hum_BodyStyle*> arr_HumBodyStyles;

// --------------------------------------



// Функция возвращает материал тела НПС
zCMaterial* Npc_GetBodyMaterial(oCNpc* pNpc)
{
	// результат функции
	zCMaterial* mat = NULL;

	// защита указателя
	if (!pNpc)
		return mat;

	// модель НПС
	zCModel* pModel = pNpc->GetModel();

	// защита указателя
	if (!pModel)
		return mat;

	// пробегаемся по всем мягким мешам модели
	for (int i = 0; i < pModel->meshSoftSkinList.GetNum(); i++)
	{
		// пробегаемся по всем группам материалов этого меша
		for (int j = 0; j < pModel->meshSoftSkinList[i]->numSubMeshes; j++)
		{
			// получаем указатель на один из материалов модели
			mat = pModel->meshSoftSkinList[i]->subMeshList[j].material;
			
			// если это материал с текстурой
			if (mat && mat->texture)
			{
				// берём название текстуры
				string texName = A (mat->GetTextureName());

				// если оно начинается на префикс "HUM_BODY"
				if (texName.StartWith("HUM_BODY") || texName.StartWith("BAB_BODY"))
					// возвращаем найденный материал
					return mat;
			}
		}
	}

	// в остальных случаях возвращаем пустой указатель
	return NULL;
}



// Функция возвращает материал головы НПС
zCMaterial* Npc_GetHeadMaterial(oCNpc* pNpc)
{
	// результат функции
	zCMaterial* mat = NULL;

	// защита указателя
	if (!pNpc)
		return mat;

	// модель НПС
	zCModel* pModel = pNpc->GetModel();

	// защита указателя
	if (!pModel)
		return mat;

	// находим узел, к которому прикреплён меш головы НПС
	zCModelNodeInst* pNode = pModel->SearchNode("BIP01 HEAD");
	
	// защита указателя
	if (!pNode)
		return mat;


	// пытаемся получить указатель на морф-меш головы, используя визуал найденного узла
	zCMorphMesh* pMorph = dynamic_cast<zCMorphMesh*>(pNode->nodeVisual);
	
	// защита указателя
	if (!pMorph)
		return mat;


	// пробегаемся по всем группам материалов меша головы
	for (int i = 0; i < pMorph->morphMesh->numSubMeshes; i++)
	{
		// берём указатель на материал
		mat = pMorph->morphMesh->subMeshList[i].material;

		// если материал существует и у него есть текстура
		if (mat && mat->texture)
		{
			// берём название текстуры
			string texName = A (mat->GetTextureName());

			// если оно начинается на префикс "HUM_HEAD"
			if (texName.StartWith("HUM_HEAD") || texName.StartWith("BAB_HEAD"))
				// возвращаем найденный материал
				return mat;
		}
	}

	// в остальных случаях возвращаем пустой указатель
	return NULL;
}



//****************
// Рендер модели
//****************
//0x00560770 public: virtual int __thiscall zCModel::Render(struct zTRenderContext &)
static int __fastcall Model_Render(zCModel* _this, void* vt, zTRenderContext& cont);
static CInvoke <int(__thiscall*)(zCModel*, zTRenderContext&)> pModel_Render(0x00560770, Model_Render, IVK_AUTO);
static int __fastcall Model_Render(zCModel* _this, void* vt, zTRenderContext& cont)
{
	// результат функции
	int res = 0;

	// НПС, которому принадлежит модель
	oCNpc* pNpc = dynamic_cast<oCNpc*>(_this->homeVob);

	// если модель не принадлежит человеку
	if (!pNpc || (pNpc && !pNpc->IsHuman()))
		// вызываем оригинал
		return pModel_Render(_this, cont);

	// Иначе:
	// получаем номер инстанции НПС
	int inst_id = pNpc->GetInstance();

	//-------------------------------
	

	// индекс текстового префикса (не задан)
	int pref_idx = -1;

	// пытаемся найти текущего НПС в общем массиве
	for (uint i = 0; i < arr_HumBodyStyles.GetNum(); i++)
	{
		// если нашли по номеру инстанции
		if (arr_HumBodyStyles[i]->inst_id == inst_id)
		{
			// копируем найденный индекс текстового префикса
			pref_idx = arr_HumBodyStyles[i]->style_idx;

			// и выходим
			break;
		}
	}
	
	// если так и не удалось найти НПС в общем массиве
	if (pref_idx < 0)
		// вызываем оригинал
		return pModel_Render(_this, cont);
	
	//------------------------------------
	
	
	// получаем указатель на материал тела НПС
	zCMaterial* pBodyMat = Npc_GetBodyMaterial(pNpc);

	// получаем указатель на материал головы НПС
	zCMaterial* pHeadMat = Npc_GetHeadMaterial(pNpc);

	// старые названия текстур тела и головы
	string oldBodyTexName = "";
	string oldHeadTexName = "";

	// первый префикс в названии текстуры
	string sFirstPrefix = "";

	// есть ли отсутствующие текстуры
	bool bPrintNotFound = false;
	//------------------------------------


	// если материал тела найден
	if (pBodyMat)
	{
		// запоминаем старое название текстуры
		oldBodyTexName = A pBodyMat->GetTextureName();

		// копируем из названия текстуры в префикс "HUM_BODY" или "BAB_BODY", формируя начальный префикс
		sFirstPrefix = oldBodyTexName.Copy(0, 8);

		// затем формируем полное название текстуры (Например: "HUM_BODY_MAGE_V10_C3")
		string newBodyTexName = sFirstPrefix + A "_" + arr_HumTypes[pref_idx] + A "_V" + A pNpc->body_TexVarNr + A "_C" + A pNpc->body_TexColorNr;
		
		// если новая текстура не найдена
		if (!TextureIsExist(newBodyTexName))
		{
			// выводим сообщение в консоль Юнион
			bPrintNotFound = Print_TexNotFound(newBodyTexName, true, pNpc);

			// только в режиме отладки
			if (debugMode)
				pBodyMat->SetTexture(Z "RED");
		}
		else
			// применяем новую текстуру к материалу
			pBodyMat->SetTexture(Z newBodyTexName);
	}
	// Если материал не найден, то произойдёт обычный рендер модели, без замены текстуры тела.


	// если материал головы найден
	if (pHeadMat)
	{
		// запоминаем старое название текстуры
		oldHeadTexName = A pHeadMat->GetTextureName();

		// копируем из названия текстуры в префикс "HUM_HEAD" или "BAB_HEAD", формируя начальный префикс
		sFirstPrefix = oldHeadTexName.Copy(0, 8);

		// затем формируем полное название текстуры (Например: HUM_HEAD_MAGE_V4_C3)
		string newHeadTexName = sFirstPrefix + A "_" + arr_HumTypes[pref_idx] + A "_V" + A pNpc->head_TexVarNr + A "_C" + A pNpc->body_TexColorNr;
		
		// если новая текстура не найдена
		if (!TextureIsExist(newHeadTexName))
		{
			// выводим сообщение в консоль Юнион
			bPrintNotFound = Print_TexNotFound(newHeadTexName, false, pNpc);

			// только в режиме отладки
			if (debugMode)
				pHeadMat->SetTexture(Z "RED");
		}
		else
			// применяем новую текстуру к материалу
			pHeadMat->SetTexture(Z newHeadTexName);
	}
	// Если материал не найден, то произойдёт обычный рендер модели, без замены текстуры головы.
	


	// формируем отступ между отдельными записями
	if (bPrintNotFound)
		cmd << endl;


	//-------------------------------


	// рендерим модель НПС
	res = pModel_Render(_this, cont);

	// если материал тела был найден
	if (pBodyMat)
		// устанавливаем старую текстуру тела
		pBodyMat->SetTexture(Z oldBodyTexName);
	
	// если материал головы был найден
	if (pHeadMat)
		// устанавливаем старую текстуру головы
		pHeadMat->SetTexture(Z oldHeadTexName);

	// выходим
	return res;
}



} /* end namespace */