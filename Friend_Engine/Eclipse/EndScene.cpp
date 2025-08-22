#include "EndScene.h"
#include "EclipseApp.h"
#include "../Direct2D_EngineLib/SceneManager.h"

void EndScene::Awake()
{
	// camera init
	cam = CreateObject<GameObject>();
	cam->AddComponent<Transform>();
	cam->AddComponent<Camera>(1920, 1080);

	// ȭ�� �Ʒ����� �����ϵ��� �ʱ� Y ��ġ ���� (ȭ�� �� �Ʒ���)
	float startY = -600.0f;  // ȭ�� �Ʒ��� �ۿ��� ����

	// create credits - ��ȹ (��� �ؽ�Ʈ ���� ũ��)
	auto planningTitle = CreateObject<UI_Text>();
	planningTitle->rectTransform->SetPosition(0, startY);
	planningTitle->rectTransform->SetSize(1920, 80);
	planningTitle->screenTextRenderer->SetFontSize(60);  // �̸��� ���� ũ��
	planningTitle->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	planningTitle->screenTextRenderer->SetText(L"��ȹ");
	planningTitle->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(planningTitle);

	auto planningTeam = CreateObject<UI_Text>();
	planningTeam->rectTransform->SetPosition(0, startY - 100);
	planningTeam->rectTransform->SetSize(1920, 80);
	planningTeam->screenTextRenderer->SetFontSize(60);
	planningTeam->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	planningTeam->screenTextRenderer->SetText(L"������  ������");
	planningTeam->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(planningTeam);

	// create credits - ��Ʈ (�� ū ����)
	auto artTitle = CreateObject<UI_Text>();
	artTitle->rectTransform->SetPosition(0, startY - 300);
	artTitle->rectTransform->SetSize(1920, 80);
	artTitle->screenTextRenderer->SetFontSize(60);  // �̸��� ���� ũ��
	artTitle->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	artTitle->screenTextRenderer->SetText(L"��Ʈ");
	artTitle->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(artTitle);

	auto artTeam = CreateObject<UI_Text>();
	artTeam->rectTransform->SetPosition(0, startY - 400);
	artTeam->rectTransform->SetSize(1920, 80);
	artTeam->screenTextRenderer->SetFontSize(60);
	artTeam->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	artTeam->screenTextRenderer->SetText(L"�չΰ�  ������");
	artTeam->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(artTeam);

	// create credits - ���� (�� ū ����)
	auto devTitle = CreateObject<UI_Text>();
	devTitle->rectTransform->SetPosition(0, startY - 600);
	devTitle->rectTransform->SetSize(1920, 80);
	devTitle->screenTextRenderer->SetFontSize(60);  // �̸��� ���� ũ��
	devTitle->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	devTitle->screenTextRenderer->SetText(L"����");
	devTitle->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(devTitle);

	// ������ ù ��° ��
	auto devTeam1 = CreateObject<UI_Text>();
	devTeam1->rectTransform->SetPosition(0, startY - 700);
	devTeam1->rectTransform->SetSize(1920, 80);
	devTeam1->screenTextRenderer->SetFontSize(60);
	devTeam1->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	devTeam1->screenTextRenderer->SetText(L"��Ʒ�  ������");
	devTeam1->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(devTeam1);

	// ������ �� ��° ��
	auto devTeam2 = CreateObject<UI_Text>();
	devTeam2->rectTransform->SetPosition(0, startY - 800);
	devTeam2->rectTransform->SetSize(1920, 80);
	devTeam2->screenTextRenderer->SetFontSize(60);
	devTeam2->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	devTeam2->screenTextRenderer->SetText(L"�����  ������");
	devTeam2->screenTextRenderer->SetFontName(L"���°���ü");
	credits.push_back(devTeam2);
}

void EndScene::Start()
{
	// game object -> SceneStart()
	__super::Start();
}

void EndScene::Update()
{
	// game object -> Update()
	__super::Update();

	// �����̽��ٷ� ���� ��ũ��
	float currentSpeed = 100.0f;  // �⺻ �ӵ��� ������
	if (Input::GetKey(' '))
	{
		currentSpeed = 300.0f;  // ���ǵ� ����
	}

	// ũ���� ��ũ�� (�Ʒ����� ���� �ö󰡵���)
	scrollY += currentSpeed * Time::GetDeltaTime();

	// ��� ũ���� ��ġ ������Ʈ - ���� �̵�
	for (size_t i = 0; i < credits.size(); ++i)
	{
		auto currentPos = credits[i]->rectTransform->GetPosition();
		credits[i]->rectTransform->SetPosition(currentPos.x, currentPos.y + currentSpeed * Time::GetDeltaTime());
	}

	//������ ȭ�� ���� �ö� �� Ÿ�̸� ���� (������ ũ������ ȭ�� ���� �ö󰬴��� Ȯ��)
	if (!isEnded && credits.size() > 0)
	{
		auto lastCreditPos = credits[credits.size() - 1]->rectTransform->GetPosition();
		if(lastCreditPos.y > 600.0f)  // ȭ�� ���� �ö󰬴��� Ȯ��
		{
			isEnded = true;  // ũ������ �������� ǥ��
			
		}
	}

//Ÿ�̸� ���� �� �� ��ȯ
	if (isEnded)
	{
		endTimer+= Time::GetDeltaTime();
		if (endTimer >= 0.5f)  // 5�� �Ŀ� �� ��ȯ
		{
			SceneManager::Get().ChangeScene(EclipseApp::MENU);  // �޴� ������ ��ȯ
		}
	}
}

void EndScene::Exit()
{
	// game object -> destroy()
	__super::Exit();
	credits.clear();
	endTimer = 0.0f;
	isEnded = false;
}