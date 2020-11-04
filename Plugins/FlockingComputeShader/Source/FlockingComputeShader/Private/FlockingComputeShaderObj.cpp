#include "FlockingComputeShaderObj.h"

#include "ComputeShaderExample.h"
#include "PixelShaderExample.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "RHI.h"
#include "GlobalShader.h"
#include "RHICommandList.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"


FlockingComputeShaderObj::~FlockingComputeShaderObj()
{
	EndRendering();
}

void FlockingComputeShaderObj::BeginRendering()
{
	if (OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}

	bCachedParametersValid = false;

	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		OnPostResolvedSceneColorHandle = RendererModule->GetResolvedSceneColorCallbacks().AddRaw(this, &FlockingComputeShaderObj::PostResolveSceneColor_RenderThread);
	}
}

void FlockingComputeShaderObj::EndRendering()
{
	if (!OnPostResolvedSceneColorHandle.IsValid())
	{
		return;
	}

	const FName RendererModuleName("Renderer");
	IRendererModule* RendererModule = FModuleManager::GetModulePtr<IRendererModule>(RendererModuleName);
	if (RendererModule)
	{
		RendererModule->GetResolvedSceneColorCallbacks().Remove(OnPostResolvedSceneColorHandle);
	}

	OnPostResolvedSceneColorHandle.Reset();
}

void FlockingComputeShaderObj::UpdateParameters(FShaderUsageExampleParameters& DrawParameters)
{
	RenderEveryFrameLock.Lock();
	CachedShaderUsageExampleParameters = DrawParameters;
	bCachedParametersValid = true;
	RenderEveryFrameLock.Unlock();
}

void FlockingComputeShaderObj::PostResolveSceneColor_RenderThread(FRHICommandListImmediate& RHICmdList, class FSceneRenderTargets& SceneContext)
{
	if (!bCachedParametersValid)
	{
		return;
	}

	// Depending on your data, you might not have to lock here, just added this code to show how you can do it if you have to.
	RenderEveryFrameLock.Lock();
	FShaderUsageExampleParameters Copy = CachedShaderUsageExampleParameters;
	RenderEveryFrameLock.Unlock();

	Draw_RenderThread(Copy);
}

void FlockingComputeShaderObj::Draw_RenderThread(const FShaderUsageExampleParameters& DrawParameters)
{
	check(IsInRenderingThread());
	if (!DrawParameters.VelocityRenderTarget)
	{
		return;
	}

	if (!DrawParameters.PositionRenderTarget)
	{
		return;
	}

	FRHICommandListImmediate& RHICmdList = GRHICommandList.GetImmediateCommandList();

	
	if (!FFlockingComputeShader::Get().VelocityOutput.IsValid())
	{
		FPooledRenderTargetDesc ComputeShaderOutputDesc(FPooledRenderTargetDesc::Create2DDesc(DrawParameters.GetRenderTargetSize(), PF_A32B32G32R32F, FClearValueBinding::None, TexCreate_None, TexCreate_ShaderResource | TexCreate_UAV, false));

		ComputeShaderOutputDesc.DebugName = TEXT("ShaderPlugin_ComputeShaderOutput");
		GRenderTargetPool.FindFreeElement(RHICmdList, ComputeShaderOutputDesc, FFlockingComputeShader::Get().VelocityOutput, TEXT("ShaderPlugin_ComputeShaderOutput"));
	}
	
	if (!PositionOutput.IsValid())
	{
		FPooledRenderTargetDesc ComputeShaderOutputDesc(FPooledRenderTargetDesc::Create2DDesc(DrawParameters.GetRenderTargetSize(), PF_A32B32G32R32F, FClearValueBinding::None, TexCreate_None, TexCreate_ShaderResource | TexCreate_UAV, false));

		ComputeShaderOutputDesc.DebugName = TEXT("ShaderPlugin_ComputeShaderOutput2");
		GRenderTargetPool.FindFreeElement(RHICmdList, ComputeShaderOutputDesc, FFlockingComputeShader::Get().PositionOutput, TEXT("ShaderPlugin_ComputeShaderOutput2"));
	}

	FComputeShaderExample::RunComputeShader_RenderThread(RHICmdList, DrawParameters, FFlockingComputeShader::Get().VelocityOutput->GetRenderTargetItem().UAV, DrawParameters.VelocityRenderTarget->GetRenderTargetResource()->TextureRHI, FFlockingComputeShader::Get().PositionOutput->GetRenderTargetItem().UAV, DrawParameters.PositionRenderTarget->GetRenderTargetResource()->TextureRHI);
	FPixelShaderExample::DrawToRenderTarget_RenderThread(RHICmdList, DrawParameters, FFlockingComputeShader::Get().VelocityOutput->GetRenderTargetItem().TargetableTexture, FFlockingComputeShader::Get().PositionOutput->GetRenderTargetItem().TargetableTexture);
}
