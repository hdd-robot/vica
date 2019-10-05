/*
 * VICA
 * gazebo_cube_spawner.h
 *  Created on: 23 déc. 2018
 *      Author: Halim DJERROUD
 *      e-mail: hdd@ai.univ-paris8.fr
 */

#ifndef WORK_GEN_IMG_SRC_GAZEBO_CUBE_SPAWNER_H_
#define WORK_GEN_IMG_SRC_GAZEBO_CUBE_SPAWNER_H_



#include <ros/ros.h>

namespace gazebo_test_tools {


class GazeboCubeSpawner {
public:
    GazeboCubeSpawner(ros::NodeHandle &n);

    void spawnCube(const std::string& name, const std::string& frame_id,
            float x, float y, float z, float qx, float qy, float qz, float qw,
            float w=0.05, float h=0.05, float d=0.05, float mass=0.05);

    void spawnRandCube(const std::string& name, const std::string& frame_id, float x, float y, float z);
    void spawnRandcylinder(const std::string& name, const std::string& frame_id, float x, float y, float z);



    /**
     * \param isCube if true, spawn a cube. If false, spawn cylinder,
     *      where \e w is the radius and \e h is the height (\e d will be ignored).
     */
    void spawnPrimitive(const std::string& name, const bool isCube,
            const std::string& frame_id,
            float x, float y, float z, float qx, float qy, float qz, float qw,
            float w=0.05, float h=0.05, float d=0.05, float mass=0.05);

    float RandomFloat(float min, float max);
private:

    ros::NodeHandle nh;
    ros::ServiceClient spawn_object;


	float length;
	float width;
	float height;

	float min_height;
	float min_width;
	float min_depth ;

	float max_height;
	float max_width;
	float max_depth;


	float min_rot_pos_x;
	float min_rot_pos_y;
	float min_rot_pos_z;

	float max_rot_pos_x;
	float max_rot_pos_y;
	float max_rot_pos_z;

};

} // namespace


#endif /* WORK_GEN_IMG_SRC_GAZEBO_CUBE_SPAWNER_H_ */
