

//********************************************************
// ������� ����������� ����� ������� ��� ��� � ����� ���
//********************************************************
namespace GOTHIC_ENGINE {

// ����� �������
extern bool debugMode;

// ������ ����������� �������
Array<string> arr_NotFoundTextures;

// ������� � ������� ����� ������������� ��������
// (������ �������� ��������� ����������, � �� ���������)
bool Print_TexNotFound(const string& texName, bool IsBodyTex, oCNpc* pNpc)
{
	// ���� ����� �������� ��� ���� � ������� ������������� �������
	if (arr_NotFoundTextures.HasEqual(texName))
		// �������, �.�. ��� ��� ���� � �������
		return false;

	// ���� �������� �� ������� � �������, �� ��������� �
	arr_NotFoundTextures.Insert(texName);

	// ����� ���������
	string msg = "";

	// �������� �������������� ��������
	if (IsBodyTex)
		msg = "Body";
	else
		msg = "Head";

	// ��������� ������ ����� ���������
	msg = msg + " texture '" + texName + A "' not found! (Npc: " + A pNpc->GetInstanceName() + A ")";

	// � ������� ��� � �������
	dllPrint(msg);

	// �������� �����
	return true;
}

//------------------------


// ������ ��������� ��������� ��� (Miner, Psionic, Mage, CookSmith...)
Array<string> arr_HumTypes;

// ��������� ����� �������
// typeName - ��������� �������� ��������
int Add_HumBodyType(const string& typeName)
{
	// ����������� �� ������� ���������
	for (uint i = 0; i < arr_HumTypes.GetNum(); i++)
	{
		// ���� ����� ������� ��� ����������
		if (arr_HumTypes[i].CompareI(typeName))
			// ���������� ��� ������
			return i;
	}

	// ���� ������� ��� � �� ������
	// ��������� ����� ������� � ������
	arr_HumTypes.InsertEnd(typeName);

	// ��������� ������� ����� ������ � ������� �������
	arr_HumTypes.GetLast().Upper();

	// � ���������� ������ ��������
	return arr_HumTypes.GetNum() - 1;
}

// ---------------------------------


// ��������� � ���������� ��� � ������� �� ��� ��������� �������
struct Hum_BodyStyle
{
	int	inst_id;	// ����� ��������� ���
	int	style_idx;	// ������ �������� (��� �������� ���� � ������)

	// �����������
	// (id - ����� ��������� ���, idx - ������ �������� � ����� ������� ���������)
	Hum_BodyStyle( int id, int idx )
	{
		inst_id = id;
		style_idx = idx;
	}
};

// ����� ������ �������� � ����������� � �������� �� �� ��������
Array<Hum_BodyStyle*> arr_HumBodyStyles;

// --------------------------------------



// ������� ���������� �������� ���� ���
zCMaterial* Npc_GetBodyMaterial(oCNpc* pNpc)
{
	// ��������� �������
	zCMaterial* mat = NULL;

	// ������ ���������
	if (!pNpc)
		return mat;

	// ������ ���
	zCModel* pModel = pNpc->GetModel();

	// ������ ���������
	if (!pModel)
		return mat;

	// ����������� �� ���� ������ ����� ������
	for (int i = 0; i < pModel->meshSoftSkinList.GetNum(); i++)
	{
		// ����������� �� ���� ������� ���������� ����� ����
		for (int j = 0; j < pModel->meshSoftSkinList[i]->numSubMeshes; j++)
		{
			// �������� ��������� �� ���� �� ���������� ������
			mat = pModel->meshSoftSkinList[i]->subMeshList[j].material;
			
			// ���� ��� �������� � ���������
			if (mat && mat->texture)
			{
				// ���� �������� ��������
				string texName = A (mat->GetTextureName());

				// ���� ��� ���������� �� ������� "HUM_BODY"
				if (texName.StartWith("HUM_BODY") || texName.StartWith("BAB_BODY"))
					// ���������� ��������� ��������
					return mat;
			}
		}
	}

	// � ��������� ������� ���������� ������ ���������
	return NULL;
}



// ������� ���������� �������� ������ ���
zCMaterial* Npc_GetHeadMaterial(oCNpc* pNpc)
{
	// ��������� �������
	zCMaterial* mat = NULL;

	// ������ ���������
	if (!pNpc)
		return mat;

	// ������ ���
	zCModel* pModel = pNpc->GetModel();

	// ������ ���������
	if (!pModel)
		return mat;

	// ������� ����, � �������� ��������� ��� ������ ���
	zCModelNodeInst* pNode = pModel->SearchNode("BIP01 HEAD");
	
	// ������ ���������
	if (!pNode)
		return mat;


	// �������� �������� ��������� �� ����-��� ������, ��������� ������ ���������� ����
	zCMorphMesh* pMorph = dynamic_cast<zCMorphMesh*>(pNode->nodeVisual);
	
	// ������ ���������
	if (!pMorph)
		return mat;


	// ����������� �� ���� ������� ���������� ���� ������
	for (int i = 0; i < pMorph->morphMesh->numSubMeshes; i++)
	{
		// ���� ��������� �� ��������
		mat = pMorph->morphMesh->subMeshList[i].material;

		// ���� �������� ���������� � � ���� ���� ��������
		if (mat && mat->texture)
		{
			// ���� �������� ��������
			string texName = A (mat->GetTextureName());

			// ���� ��� ���������� �� ������� "HUM_HEAD"
			if (texName.StartWith("HUM_HEAD") || texName.StartWith("BAB_HEAD"))
				// ���������� ��������� ��������
				return mat;
		}
	}

	// � ��������� ������� ���������� ������ ���������
	return NULL;
}



//****************
// ������ ������
//****************
//0x00560770 public: virtual int __thiscall zCModel::Render(struct zTRenderContext &)
static int __fastcall Model_Render(zCModel* _this, void* vt, zTRenderContext& cont);
static CInvoke <int(__thiscall*)(zCModel*, zTRenderContext&)> pModel_Render(0x00560770, Model_Render, IVK_AUTO);
static int __fastcall Model_Render(zCModel* _this, void* vt, zTRenderContext& cont)
{
	// ��������� �������
	int res = 0;

	// ���, �������� ����������� ������
	oCNpc* pNpc = dynamic_cast<oCNpc*>(_this->homeVob);

	// ���� ������ �� ����������� ��������
	if (!pNpc || (pNpc && !pNpc->IsHuman()))
		// �������� ��������
		return pModel_Render(_this, cont);

	// �����:
	// �������� ����� ��������� ���
	int inst_id = pNpc->GetInstance();

	//-------------------------------
	

	// ������ ���������� �������� (�� �����)
	int pref_idx = -1;

	// �������� ����� �������� ��� � ����� �������
	for (uint i = 0; i < arr_HumBodyStyles.GetNum(); i++)
	{
		// ���� ����� �� ������ ���������
		if (arr_HumBodyStyles[i]->inst_id == inst_id)
		{
			// �������� ��������� ������ ���������� ��������
			pref_idx = arr_HumBodyStyles[i]->style_idx;

			// � �������
			break;
		}
	}
	
	// ���� ��� � �� ������� ����� ��� � ����� �������
	if (pref_idx < 0)
		// �������� ��������
		return pModel_Render(_this, cont);
	
	//------------------------------------
	
	
	// �������� ��������� �� �������� ���� ���
	zCMaterial* pBodyMat = Npc_GetBodyMaterial(pNpc);

	// �������� ��������� �� �������� ������ ���
	zCMaterial* pHeadMat = Npc_GetHeadMaterial(pNpc);

	// ������ �������� ������� ���� � ������
	string oldBodyTexName = "";
	string oldHeadTexName = "";

	// ������ ������� � �������� ��������
	string sFirstPrefix = "";

	// ���� �� ������������� ��������
	bool bPrintNotFound = false;
	//------------------------------------


	// ���� �������� ���� ������
	if (pBodyMat)
	{
		// ���������� ������ �������� ��������
		oldBodyTexName = A pBodyMat->GetTextureName();

		// �������� �� �������� �������� � ������� "HUM_BODY" ��� "BAB_BODY", �������� ��������� �������
		sFirstPrefix = oldBodyTexName.Copy(0, 8);

		// ����� ��������� ������ �������� �������� (��������: "HUM_BODY_MAGE_V10_C3")
		string newBodyTexName = sFirstPrefix + A "_" + arr_HumTypes[pref_idx] + A "_V" + A pNpc->body_TexVarNr + A "_C" + A pNpc->body_TexColorNr;
		
		// ���� ����� �������� �� �������
		if (!TextureIsExist(newBodyTexName))
		{
			// ������� ��������� � ������� �����
			bPrintNotFound = Print_TexNotFound(newBodyTexName, true, pNpc);

			// ������ � ������ �������
			if (debugMode)
				pBodyMat->SetTexture(Z "RED");
		}
		else
			// ��������� ����� �������� � ���������
			pBodyMat->SetTexture(Z newBodyTexName);
	}
	// ���� �������� �� ������, �� ��������� ������� ������ ������, ��� ������ �������� ����.


	// ���� �������� ������ ������
	if (pHeadMat)
	{
		// ���������� ������ �������� ��������
		oldHeadTexName = A pHeadMat->GetTextureName();

		// �������� �� �������� �������� � ������� "HUM_HEAD" ��� "BAB_HEAD", �������� ��������� �������
		sFirstPrefix = oldHeadTexName.Copy(0, 8);

		// ����� ��������� ������ �������� �������� (��������: HUM_HEAD_MAGE_V4_C3)
		string newHeadTexName = sFirstPrefix + A "_" + arr_HumTypes[pref_idx] + A "_V" + A pNpc->head_TexVarNr + A "_C" + A pNpc->body_TexColorNr;
		
		// ���� ����� �������� �� �������
		if (!TextureIsExist(newHeadTexName))
		{
			// ������� ��������� � ������� �����
			bPrintNotFound = Print_TexNotFound(newHeadTexName, false, pNpc);

			// ������ � ������ �������
			if (debugMode)
				pHeadMat->SetTexture(Z "RED");
		}
		else
			// ��������� ����� �������� � ���������
			pHeadMat->SetTexture(Z newHeadTexName);
	}
	// ���� �������� �� ������, �� ��������� ������� ������ ������, ��� ������ �������� ������.
	


	// ��������� ������ ����� ���������� ��������
	if (bPrintNotFound)
		cmd << endl;


	//-------------------------------


	// �������� ������ ���
	res = pModel_Render(_this, cont);

	// ���� �������� ���� ��� ������
	if (pBodyMat)
		// ������������� ������ �������� ����
		pBodyMat->SetTexture(Z oldBodyTexName);
	
	// ���� �������� ������ ��� ������
	if (pHeadMat)
		// ������������� ������ �������� ������
		pHeadMat->SetTexture(Z oldHeadTexName);

	// �������
	return res;
}



} /* end namespace */