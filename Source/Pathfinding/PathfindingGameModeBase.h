// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Public/MyNode.h"
#include "PathfindingGameModeBase.generated.h"

class AMyNode;

/**
 * The class that controls and keeps the top level functions and
 * variables to use in all the pathfinding algorithms.
 */
UCLASS()
class PATHFINDING_API APathfindingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	APathfindingGameModeBase();

	virtual void BeginPlay() override;

public:

	// The number of nodes to spawn
	UPROPERTY(EditAnywhere, Category = "Node")
	int32 NumberOfNodes;

	// Radius from each node before it connects with another
	UPROPERTY(EditAnywhere, Category = "Node")
	int32 NodeConnectionRadius;

	// Array containing pointers to all spawned nodes
	UPROPERTY(EditAnywhere, Category = "Node")
	TArray<AMyNode*> Nodes;

	// Location of the previous node spawned
	FVector PrevLoc;

	// The required distance between each node
	UPROPERTY(EditAnywhere, Category = "Node")
	int32 NodeDist;

	// Whether to draw the bounds that the nodes spawn in
	UPROPERTY(EditAnywhere)
	bool DrawBounds;

	UPROPERTY(EditAnywhere, Category = "Node")
	TSubclassOf<AMyNode> BP_MyNode;


	//---------------- Functions -------------------//

	// Spawns nodes with a random location within the specified bounds
	void SpawnNodes();

	// Iterates through each node and makes connections to the closest ones
	void SetupNodeConnections();

	/**
	 * @brief Set each node's collision component to NodeConnectionRadius
	 */
	void UpdateNodeOverlapSpheres();

	/**
	 * @brief Add each node to each other's connection arrays,
	 * and draw a line between them.
	 */
	void MakeConnection(AMyNode* n1, AMyNode* n2);

	/**
	 * @brief Does item exist in arr?
	 * @tparam T Datatype
	 * @param arr The array to search in
	 * @param item The item to search for
	 * @return Whether the item was found in arr.
	 */
	template<class T>
	bool in(TArray<T> arr, T item);

	/**
	 * @brief Draw a debug line between the two passed nodes.
	 */
	void DrawLine(AMyNode* n1, AMyNode* n2, FColor Color = FColor::White) const;
};

template <class T>
bool APathfindingGameModeBase::in(TArray<T> arr, T item)
{
	//for (auto obj : arr)
	for (int32 i{}; i < arr.Num(); i++)
	{
		if (arr[i] == item) return true;
	}
	return false;
}
