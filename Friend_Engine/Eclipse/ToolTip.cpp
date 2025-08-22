#include "tooltip.h"
#include <string>
#include <locale>
#include <codecvt>

static std::string ToString(const std::wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

void tooltip::Awake()
{
	rectTransform = AddComponent<RectTransform>();
	tooltipBackGround_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	tooltip_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	tooltipName_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	tooltipDescribe_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();

	tooltipBackGround_Image->rectTransform->SetParent(rectTransform);
	tooltip_Image->rectTransform->SetParent(tooltipBackGround_Image->rectTransform);
	tooltipName_Text->rectTransform->SetParent(tooltipBackGround_Image->rectTransform);
	tooltipDescribe_Text->rectTransform->SetParent(tooltipBackGround_Image->rectTransform);

	textInfo.clear();

	//���� �ؽ�Ʈ ���� �ʱ�ȭ
	textInfo[L"Ignis"] = {L"�̱״Ͻ�", L"���� ��ȥ��\n�浹�ϸ�\n�������� Ŀ����."};
	textInfo[L"Umbra"] = { L"�����", L"���� ��ȥ��\n�浹�ϸ�\n�ѷ� �и��ȴ�." };
	textInfo[L"Dark"] = { L"��ũ", L"���� ��ȥ��\n�浹�ϸ�\n�ֺ��� �������." };
	textInfo[L"Luna"] = {L"�糪", L"�ı��� ���\nȥ�� �Ҵ´�."};
	textInfo[L"Nox"] = {L"�콺", L"��ȥ�� �浹����\n������� �� �� �ִ�.\n���� ��� ����,\n��� ���� ������."};		

	SetActive(false);
}

void tooltip::SceneStart()
{
	tooltipBackGround_Image->rectTransform->SetSize(300, 200);
	auto toolTipTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/ToolTip.png");
	tooltipBackGround_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(toolTipTexture, "ToolTip");

	tooltip_Image->rectTransform->SetPosition(-80,25);
	tooltip_Image->rectTransform->SetSize(80, 80);

	tooltipName_Text->rectTransform->SetPosition(-80, -50);
	tooltipName_Text->rectTransform->SetSize(90, 50);
	tooltipName_Text->screenTextRenderer->SetFontSize(30);
	tooltipName_Text->screenTextRenderer->SetFontName(L"���°���ü");
	tooltipName_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));

	tooltipDescribe_Text->rectTransform->SetPosition(45, 0);
	tooltipDescribe_Text->rectTransform->SetSize(160, 50);
	tooltipDescribe_Text->screenTextRenderer->SetFontSize(17);
	tooltipDescribe_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));

}

void tooltip::Update()
{
}

void tooltip::Destroyed()
{
	textInfo.clear();
}

void tooltip::ChangeInfo(const std::wstring& name)
{
	if (name == L"Ignis") rectTransform->SetPosition(775, -200);
	else if (name == L"Umbra") rectTransform->SetPosition(775, -400);
	else rectTransform->SetPosition(775 , -300);

	auto it = textInfo.find(name);
	if (it != textInfo.end())
	{
		tooltipName_Text->screenTextRenderer->SetText(it->second.skillname);
		tooltipDescribe_Text->screenTextRenderer->SetText(it->second.skillDesc); 
		std::wstring fullPathW = L"../Resource/mo/" + name + L"_Tooltip.png";
		auto tooltipImageTexture = ResourceManager::Get().CreateTexture2D(ToString(fullPathW));
		tooltip_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(tooltipImageTexture, ToString(fullPathW));
		SetActive(true);
	}
	else
	{
		tooltipName_Text->screenTextRenderer->SetText(L"");
		tooltipDescribe_Text->screenTextRenderer->SetText(L"");
		SetActive(false);
	}
}