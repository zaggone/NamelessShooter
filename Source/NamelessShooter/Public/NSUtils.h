#pragma once
class NSUtils
{
public:
	static void AttachToSocket(AActor* Actor, USceneComponent* SceneComponent, const FName& SocketName)
	{
		if (!Actor || !SceneComponent) return;
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		Actor->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
	}

};