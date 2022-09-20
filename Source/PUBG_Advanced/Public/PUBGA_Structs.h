#pragma once
#include "Engine/DataTable.h"
#include "PUBGA_Structs.generated.h"


USTRUCT(BlueprintType)
struct FSTR_ProneTimes : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Sec;


};


USTRUCT(BlueprintType)
struct FSTR_CameraHeight : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;


};

USTRUCT(BlueprintType)
struct FSTR_WalkSpeed : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Other;

};





