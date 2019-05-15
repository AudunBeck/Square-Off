#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "CameraSetUp.generated.h"

UCLASS()
class UN_EZ_API ACameraSetUp : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraSetUp();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float minArmLength;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float maxArmLength;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		FVector offsetCam;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float spawnerOffset;

	UPROPERTY(EditAnywhere, Category = "CameraMovement")
		float maxCameraChange; 

	UPROPERTY(EditAnywhere, Category = "CameraMovement")
		int playerWon = 0;

	UPROPERTY(EditAnywhere, Category = "CameraMovement")
		bool winningCam = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* StageCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<APlayerController*> playerControllers;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FVector>pawnLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector centerLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float furthestPawn;

	UFUNCTION(BlueprintCallable, Category = "CameraMovement")
		void winningPlayer(int winner);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CameraVariables")
		int playerAmount = 0;

	bool test = false;
	void findPlayerControllers();
	void getPawnLocations();
	void calculateCenterLocation();
	void setCameraPosition(float DeltaTime);
	void winCamPos(float DeltaTime);


};
