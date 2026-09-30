//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <d3d11.h>
#include <d3dcompiler.h>
#include <WinUser.h>
#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "include\Camera.h"
#include "include\Colors.h"
#include "include\GameObject.h"
#include "include\ShaderObject.h"
#include "include\ShaderObject_LightTexture.h"
#include "include\MeshProto.h"
#include "include\GraphicsObject_LightTexture.h"
#include "include\GameObjectMan.h"
#include "include\MeshNodeMan.h"
#include "include\ShaderObjectNodeMan.h"
#include "include\TextureProto.h"
#include "include\TexNodeMan.h"
#include "include\DirectXDeviceMan.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "Game.h"
#include "GameApp.h"

GameApp *GameApp::pInstance = nullptr;

GameApp *GameApp::privGameApp()
{
	if(GameApp::pInstance == nullptr)
	{
		GameApp::pInstance = new GameApp();
	}
	
	return GameApp::pInstance;
}

GameApp::GameApp()
{
	this->pHackCamera = nullptr;
	this->pGame = nullptr;
}

void GameApp::LoadDemo(Game *_pGame)
{
	GameApp *pGameApp = GameApp::privGameApp();
	pGameApp->pGame = _pGame;

	ShaderObjectNodeMan::Create();
	MeshNodeMan::Create();
	GameObjectMan::Create();
	TexNodeMan::Create();

	// ---------------------------------
	//  Camera - Setup
	// ---------------------------------
	{
		pGameApp->pHackCamera = new Camera();
		assert(pGameApp->pHackCamera);

		Vec3 camPos(0.0f, 35.0f, 82.0f);
		Vec3 tarVect(0.0f, -3.0f, 20.0f);
		Vec3 upVect(0.0f, 0.9f, -0.4f);

		pGameApp->pHackCamera->setOrientAndPosition(upVect, tarVect, camPos);

		float AspectRatio = (float)pGameApp->pGame->WindowWidth / (float)pGameApp->pGame->WindowHeight;
		pGameApp->pHackCamera->setPerspective(55.0f, AspectRatio, 0.1f, 1000.0f);
	}

	// ------------------------------------------
	//   Model + Shaders --> GraphicsObject
	// -------------------------------------------
	{
		// ---------------------------------
		//  Model - Cube
		// ---------------------------------
		Mesh *pCrateMesh = new MeshProto("space_frigate.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);

		TextureObject *pTexCrate = new TextureProto("space_frigate.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Crate, pTexCrate);

		// --------------------------------
		//  ShaderObject  ColorByVertex
		// --------------------------------
		ShaderObject *poShaderC = new ShaderObject_LightTexture(ShaderObject::Name::LightTexture);
		ShaderObjectNodeMan::Add(poShaderC);

		// --------------------------------
		//  Graphics Object -- needs model + shader
		// --------------------------------
		Vec3 LightColor(1.50f, 1.50f, 1.50f);
		Vec3 LightPos(1.0f, 1.0f, 100.0f);

		GraphicsObject *pGraphicsObject = new GraphicsObject_LightTexture(pGameApp->pHackCamera,
																		  pCrateMesh,
																		  poShaderC,
																		  pTexCrate,
																		  LightColor,
																		  LightPos);

		GameObject *pGameObj = new GameObject(pGraphicsObject);
		pGameObj->SetName("Dave");
		pGameObj->SetPos(Vec3(0, 0, 0));
		pGameObj->SetScale(1.1f);

		GameObjectMan::Add(pGameObj);
	}
}

void GameApp::UpdateDemo()
{
	GameApp *pGameApp = GameApp::privGameApp();

	// ------------------------------------
	// Update the camera once per frame
	// ------------------------------------
	pGameApp->pHackCamera->updateCamera();
	GameObjectMan::Update();
}

void GameApp::DrawDemo()
{
	GameApp *pGameApp = GameApp::privGameApp();

	pGameApp->SetDefaultTargetMode();
	GameObjectMan::Draw();
}

void GameApp::ClearDemo()
{
	GameApp *pGameApp = GameApp::privGameApp();

#ifdef _DEBUG
	const Vec4 ClearColor = Azul::Colors::SeaGreen;// LightGreen;// Wheat;
#else
	const Vec4 ClearColor = {0.86078455f, 0.984313786f, 0.86078455f, 1.000000000f};
#endif
	float clearDepth = 1.0f;
	uint8_t clearStencil = 0;
	pGameApp->pGame->g_d3dDeviceContext->ClearRenderTargetView(pGameApp->pGame->g_d3dRenderTargetView, 
															   (const float *)&ClearColor);
	pGameApp->pGame->g_d3dDeviceContext->ClearDepthStencilView(pGameApp->pGame->g_d3dDepthStencilView, 
															   D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
															   clearDepth, 
															   clearStencil);
}

void GameApp::UnloadDemo()
{
	delete GameApp::pInstance;
}

GameApp::~GameApp()
{
	GameApp *pGameApp = GameApp::privGameApp();
	delete pGameApp->pHackCamera;

	ShaderObjectNodeMan::Destroy();
	MeshNodeMan::Destroy();
	GameObjectMan::Destroy();
	TexNodeMan::Destroy();
	DirectXDeviceMan::Destroy();
}

void GameApp::SetDefaultTargetMode()
{
	GameApp *pGameApp = GameApp::privGameApp();

	assert(pGameApp->pGame->g_d3dDevice);
	assert(pGameApp->pGame->g_d3dDeviceContext);
	//--------------------------------------------------------
	// Set (point to ) the Rasterizers functions to be used
	//--------------------------------------------------------
	pGameApp->pGame->g_d3dDeviceContext->RSSetState(pGameApp->pGame->g_d3dRasterizerState);

	//--------------------------------------------------------
	// Set (point to ) the Viewport to be used
	//--------------------------------------------------------
	pGameApp->pGame->g_d3dDeviceContext->RSSetViewports(1, &pGameApp->pGame->g_Viewport);

	//--------------------------------------------------------
	// Set (point to ) render target
	//      Only one Target, this maps to Pixel shader
	// --------------------------------------------------------
	pGameApp->pGame->g_d3dDeviceContext->OMSetRenderTargets(1, &pGameApp->pGame->g_d3dRenderTargetView, pGameApp->pGame->g_d3dDepthStencilView);

	//--------------------------------------------------------
	// Set (point to ) the Depth functions to be used
	//--------------------------------------------------------
	pGameApp->pGame->g_d3dDeviceContext->OMSetDepthStencilState(pGameApp->pGame->g_d3dDepthStencilState, 1);
}

//---  End of File ---
