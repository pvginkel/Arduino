#include "ScenesCluster.h"

ScenesCluster::ScenesCluster()
	: ZHA_Cluster(SCENES_CLUSTER_ID) {
    setAttribute(SCENES_CLUSTER_ATTRIBUTE_SCENE_COUNT, ZHA_TYPE_UINT8, 0x00);
    setAttribute(SCENES_CLUSTER_ATTRIBUTE_CURRENT_SCENE, ZHA_TYPE_UINT8, 0x00);
    setAttribute(SCENES_CLUSTER_ATTRIBUTE_CURRENT_GROUP, ZHA_TYPE_UINT16, 0x0000);
    setAttribute(SCENES_CLUSTER_ATTRIBUTE_SCENE_VALID, ZHA_TYPE_BOOL, 0x00);
    setAttribute(SCENES_CLUSTER_ATTRIBUTE_NAME_SUPPORT, ZHA_TYPE_BITMAP8, 0x0000);
}
