#pragma once


#include "CoreMinimal.h"
#include "FQueueableSound.generated.h"

USTRUCT(BlueprintType)
struct FQueueableSound {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
		class USoundBase* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fade)
		bool FadeIn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fade, meta = (EditCondition = "FadeIn"))
		float FadeInDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fade)
		bool FadeOut;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Fade, meta = (EditCondition = "FadeOut"))
		float FadeOutDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Delay)
		bool Delay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Delay, meta = (EditCondition = "Delay"))
		float DelayDuration;
};