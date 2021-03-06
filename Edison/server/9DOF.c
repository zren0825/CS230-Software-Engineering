#include "9DOF.h"

// initialize sensors, set scales, and calculate resolution
NINEDOF *ninedof_init(accel_scale_t a, gyro_scale_t g, mag_scale_t m) 
{
	NINEDOF *ninedof;
	ninedof = malloc(sizeof(NINEDOF));

	ninedof->a_scale = a;
	ninedof->g_scale = g;
	ninedof->m_scale = m;

	// initialize sensors
	ninedof->accel = accel_init();
	ninedof->gyro = gyro_init();
	ninedof->mag = mag_init();

	//set scale
	set_accel_scale(ninedof->accel, ninedof->a_scale);
	set_gyro_scale(ninedof->gyro, ninedof->g_scale);
	set_mag_scale(ninedof->mag, ninedof->m_scale);

	//set sample rate setup
	set_accel_ODR(ninedof->accel, A_ODR_800);
	set_gyro_ODR(ninedof->gyro, G_ODR_760_BW_50);
	set_mag_ODR(ninedof->mag, M_ODR_100);

	//calculate resolution
	ninedof->a_res = calc_accel_res(ninedof->a_scale);
	ninedof->g_res = calc_gyro_res(ninedof->g_scale);
	ninedof->m_res = calc_mag_res(ninedof->m_scale);

	ninedof->gyro_offset = calc_gyro_offset(ninedof->gyro, ninedof->g_res);

	return ninedof;
}

void ninedof_read(NINEDOF *ninedof) 
{
	// read accel, gyro, mag, and temperature
	ninedof->accel_data = read_accel(ninedof->accel, ninedof->a_res);
	ninedof->gyro_data = read_gyro(ninedof->gyro, ninedof->g_res);
	ninedof->mag_data = read_mag(ninedof->mag, ninedof->m_res);
	ninedof->temperature = read_temp(ninedof->accel);
}

void ninedof_print(NINEDOF* ninedof)
{
	// print 9DOF accel, gyro, mag, and temperature
	printf("X Accel: %f\t Y Accel: %f\t Z Accel: %f\t||", ninedof->accel_data.x, 
		ninedof->accel_data.y, ninedof->accel_data.z);
  	printf("\tX Gyro: %f\t Y Gyro: %f\t Z Gyro: %f\t||", 
  		ninedof->gyro_data.x - ninedof->gyro_offset.x, 
  		ninedof->gyro_data.y - ninedof->gyro_offset.y, 
  		ninedof->gyro_data.z - ninedof->gyro_offset.z);
	printf("\tX Mag: %f\t Y Mag: %f\t Z Mag: %f\t||", 
		ninedof->mag_data.x, ninedof->mag_data.y, ninedof->mag_data.z);
	printf("\tTemperature: %ld\n", ninedof->temperature);
}



