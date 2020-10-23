// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FMyVRDemo : public IModuleInterface {

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//must override this, otherwise the complie btn in the Editor will disapper.
	virtual bool IsGameModule() const override
	{
		return true;
	}
};