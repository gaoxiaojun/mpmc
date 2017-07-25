#include "System.h"
extern int rank;
extern int size;



void System::update_root_averages( observables_t *observables )
{

	double particle_mass=0, curr_density;
	double frozen_mass = observables->frozen_mass;

	Molecule   * molecule_ptr = nullptr;
	static int   counter      = 0;
	double       m            = 0,
	             factor       = 0,
	             gammaratio   = 0,
	             sdom         = 0; 

	++counter;

	if( ensemble = ENSEMBLE_NVT_GIBBS )
		m = (double)((counter-1) / 2);
	else
		m = (double) counter;



	sdom   = 1.0 / sqrt(m-1.0); // common factor in std deviation calcs that follow
	if (m == 0.0) {
		factor = 0;
		m = 1.0;
	}
	else
		factor = (m - 1.0) / m; // % of observable that old average represents after 
	                            // new data is added to the mix.


	// the physical observables 
	avg_observables->energy = factor*avg_observables->energy 
		+ observables->energy / m;
	avg_observables->energy_sq = factor*avg_observables->energy_sq 
		+ (observables->energy*observables->energy) / m;
	avg_observables->energy_error = sdom * sqrt(avg_observables->energy_sq  
		- avg_observables->energy*avg_observables->energy);

	avg_observables->energy_sq_sq = factor*avg_observables->energy_sq_sq 
		+ pow(observables->energy, 4) / m;
	avg_observables->energy_sq_error = sdom*sqrt(avg_observables->energy_sq_sq  
		- pow(avg_observables->energy, 4));

	avg_observables->coulombic_energy = factor*avg_observables->coulombic_energy 
		+ observables->coulombic_energy / m;
	avg_observables->coulombic_energy_sq = factor*avg_observables->coulombic_energy_sq 
		+ (observables->coulombic_energy*observables->coulombic_energy) / m;
	avg_observables->coulombic_energy_error = sdom*sqrt(avg_observables->coulombic_energy_sq  
		- avg_observables->coulombic_energy*avg_observables->coulombic_energy);

	avg_observables->rd_energy = factor*avg_observables->rd_energy 
		+ observables->rd_energy / m;
	avg_observables->rd_energy_sq = factor*avg_observables->rd_energy_sq 
		+ (observables->rd_energy*observables->rd_energy) / m;
	avg_observables->rd_energy_error = sdom*sqrt(avg_observables->rd_energy_sq  
		- avg_observables->rd_energy*avg_observables->rd_energy);

	avg_observables->polarization_energy = factor*avg_observables->polarization_energy 
		+ observables->polarization_energy / m;
	avg_observables->polarization_energy_sq = factor*avg_observables->polarization_energy_sq 
		+ (observables->polarization_energy*observables->polarization_energy) / m;
	avg_observables->polarization_energy_error = sdom*sqrt(avg_observables->polarization_energy_sq  
		- avg_observables->polarization_energy*avg_observables->polarization_energy);

	avg_observables->vdw_energy = factor*avg_observables->vdw_energy 
		+ observables->vdw_energy / m;
	avg_observables->vdw_energy_sq = factor*avg_observables->vdw_energy_sq 
		+ (observables->vdw_energy*observables->vdw_energy) / m;
	avg_observables->vdw_energy_error = sdom*sqrt(avg_observables->vdw_energy_sq  
		- avg_observables->vdw_energy*avg_observables->vdw_energy);
	
	avg_observables->three_body_energy = factor*avg_observables->three_body_energy 
		+ observables->three_body_energy / m;
	avg_observables->three_body_energy_sq = factor*avg_observables->three_body_energy_sq 
		+ (observables->three_body_energy*observables->three_body_energy) / m;
	avg_observables->three_body_energy_error = sdom*sqrt(avg_observables->three_body_energy_sq  
		- avg_observables->three_body_energy*avg_observables->three_body_energy);

	avg_observables->dipole_rrms = factor*avg_observables->dipole_rrms 
		+ observables->dipole_rrms / m;
	avg_observables->dipole_rrms_sq = factor*avg_observables->dipole_rrms_sq 
		+ (observables->dipole_rrms*observables->dipole_rrms) / m;
	avg_observables->dipole_rrms_error = sdom*sqrt(avg_observables->dipole_rrms_sq  
		- avg_observables->dipole_rrms*avg_observables->dipole_rrms);

	avg_observables->kinetic_energy = factor*avg_observables->kinetic_energy 
		+ observables->kinetic_energy / m;
	avg_observables->kinetic_energy_sq = factor*avg_observables->kinetic_energy_sq 
		+ (observables->kinetic_energy*observables->kinetic_energy) / m;
	avg_observables->kinetic_energy_error = sdom*sqrt(avg_observables->kinetic_energy_sq  
		- avg_observables->kinetic_energy*avg_observables->kinetic_energy);

	avg_observables->temperature = factor*avg_observables->temperature 
		+ observables->temperature / m;
	avg_observables->temperature_sq = factor*avg_observables->temperature_sq 
		+ (observables->temperature*observables->temperature) / m;
	avg_observables->temperature_error = sdom*sqrt(avg_observables->temperature_sq 
		- avg_observables->temperature*avg_observables->temperature);

	avg_observables->volume = factor*avg_observables->volume 
		+ observables->volume / m;
	avg_observables->volume_sq = factor*avg_observables->volume_sq 
		+ (observables->volume*observables->volume) / m;
	avg_observables->volume_error = sdom*sqrt(avg_observables->volume_sq  
		- avg_observables->volume*avg_observables->volume);

	avg_observables->N = factor*avg_observables->N 
		+ observables->N / m;
	avg_observables->N_sq = factor*avg_observables->N_sq 
		+ (observables->N*observables->N) / m;
	avg_observables->N_error = sdom*sqrt(avg_observables->N_sq  
		- avg_observables->N*avg_observables->N);

	avg_observables->spin_ratio = factor*avg_observables->spin_ratio 
		+ observables->spin_ratio / m;
	avg_observables->spin_ratio_sq = factor*avg_observables->spin_ratio_sq 
		+ (observables->spin_ratio*observables->spin_ratio) / m;
	avg_observables->spin_ratio_error = sdom*sqrt(avg_observables->spin_ratio_sq  
		- avg_observables->spin_ratio*avg_observables->spin_ratio);

	avg_observables->NU = factor*avg_observables->NU 
		+ observables->NU / m;

	// particle mass will be used in calculations for single sorbate systems
	for(molecule_ptr = molecules; molecule_ptr; molecule_ptr = molecule_ptr->next) 
		if( !molecule_ptr->frozen && !molecule_ptr->adiabatic)
			particle_mass = molecule_ptr->mass;

	// density in g/cm^3  (had to modify since density isn't neccessarily constant since adding NPT)
	curr_density = observables->N * particle_mass / (pbc.volume*NA*A32CM3);

	avg_observables->density = factor*avg_observables->density 
		+ curr_density/m;
	avg_observables->density_sq = factor * avg_observables->density_sq 
		+ (curr_density*curr_density)/m;
	avg_observables->density_error = sdom*sqrt(avg_observables->density_sq 
		- (avg_observables->density)*(avg_observables->density) );

	// needed for calculating sstdev (stdev of stdev) 
	//gammaratio = tgamma(0.5*(double)counter) / tgamma(0.5*((double)counter-1));
	//gammaratio = sqrt(1.0/counter * ((double)counter - 1.0 - 2.0*gammaratio*gammaratio) );
	
	//stirling approx to avoid numerical overflow
	gammaratio = pow((m-2.0)/(m-1.0),0.5*m-1.0)*sqrt(0.5*(m-2.0))*exp(0.5);
	gammaratio = sqrt(1.0/counter * (m - 1.0 - 2.0*gammaratio*gammaratio) );
	
	// heat capacity in kJ/mol K
	avg_observables->heat_capacity = (kB*NA/1000.0)*(avg_observables->energy_sq 
		- avg_observables->energy*avg_observables->energy)/(temperature*temperature);
	// error in heat capacity is the standard deviation of the variance, = 2*sstdev
	avg_observables->heat_capacity_error = sdom * 2.0 * gammaratio * avg_observables->heat_capacity;

	// compressibility
	if( ensemble != ENSEMBLE_NPT )
		avg_observables->compressibility = ATM2PASCALS*(pbc.volume/pow(METER2ANGSTROM, 3))*(avg_observables->N_sq 
			- avg_observables->N*avg_observables->N)/(kB*temperature*avg_observables->N*avg_observables->N);
	else 
		avg_observables->compressibility = ATM2PASCALS * pow(METER2ANGSTROM,-3) *
			( avg_observables->volume_sq - avg_observables->volume * avg_observables->volume ) / 
			( kB * temperature * avg_observables->volume );
	avg_observables->compressibility_error = sdom * 2.0 * gammaratio * avg_observables->compressibility;

	// we have a solid phase
	if(frozen_mass > 0.0) {

		// percent weight
		avg_observables->percent_wt = 100.0*avg_observables->N*particle_mass/(frozen_mass 
			+ avg_observables->N*particle_mass);
		avg_observables->percent_wt_error = sdom * 100.0*avg_observables->N_error*particle_mass/(frozen_mass 
			+ avg_observables->N_error*particle_mass);

		// percent weight like ME
		avg_observables->percent_wt_me = 100.0*avg_observables->N*particle_mass/frozen_mass;
		avg_observables->percent_wt_me_error = sdom * 100.0*avg_observables->N_error*particle_mass/frozen_mass;

		// excess weight mg/g
		if( free_volume > 0.0 ) {

			if( fugacities )
				avg_observables->excess_ratio = 1000.0*(avg_observables->N*particle_mass 
					- (particle_mass*free_volume*fugacities[0]*ATM2REDUCED)/temperature)/frozen_mass;
			else
				avg_observables->excess_ratio = 1000.0*(avg_observables->N*particle_mass 
					- (particle_mass*free_volume*pressure*ATM2REDUCED)/temperature)/frozen_mass;
			avg_observables->excess_ratio_error = sdom * 1000.0*avg_observables->N_error*particle_mass/frozen_mass;


			// pore density (only valid for pure, constant V systems)
			avg_observables->pore_density = curr_density * pbc.volume / free_volume;
			avg_observables->pore_density_error = sdom * avg_observables->N_error*particle_mass/(free_volume*NA*A32CM3);

		}

		// calculate the isosteric heat
		avg_observables->qst = -(avg_observables->NU 
			- avg_observables->N*avg_observables->energy);
		avg_observables->qst /= (avg_observables->N_sq 
			- avg_observables->N*avg_observables->N);
		avg_observables->qst += temperature;
		avg_observables->qst *= kB*NA/1000.0;	// convert to kJ/mol

	}

	return;
}




// update the stats for the individual sorbates
void System::update_sorbate_info() {

	// molecule_t *molecule_ptr;  (unused variable)

	double sorbed_mass, pressure;
	int i;

	//update the number of particles of each sorbate
	count_sorbates();

	for ( i=0; i<sorbateCount; i++ ) {

		if ( h2_fugacity || co2_fugacity || ch4_fugacity || n2_fugacity )
			pressure = fugacities[0];
		else if( user_fugacities )
			pressure = fugacities[i];
		else
			pressure = pressure;
		
		sorbed_mass = sorbateInfo[i].currN * sorbateInfo[i].mass;

		sorbateInfo[i].percent_wt = 100.0 * sorbed_mass/(observables->total_mass);
		sorbateInfo[i].percent_wt_me = 100.0 * sorbed_mass/(observables->frozen_mass);
		sorbateInfo[i].excess_ratio = 1000.0 * sorbateInfo[i].mass * (sorbateInfo[i].currN - 
			sorbateInfo[i].mass*free_volume*pressure*ATM2REDUCED/temperature)/observables->frozen_mass;
		sorbateInfo[i].density = sorbed_mass/(observables->volume*NA*A32CM3);
		sorbateInfo[i].pore_density = sorbed_mass/(free_volume*NA*A32CM3);

	}

	return;
}




void System::update_root_sorb_averages( sorbateInfo_t * sinfo ) {
	
	//sorbateGlobal is an array. sorbateStats is a linked list.

	static int counter = 0;
	double m, factor, sdom;
	double numerator, denominator, relative_err;

	++counter;
	m = (double)counter;
	sdom = 1.0/sqrt(m-1.0);
	factor = (m - 1.0)/m;

	// for each sorbate
	for ( int i = 0; i < sorbateCount; i++ ) {

		sorbateGlobal[i].avgN = factor * sorbateGlobal[i].avgN
			+ sinfo[i].currN / m;
		sorbateGlobal[i].avgN_sq = factor * sorbateGlobal[i].avgN_sq
			+ sinfo[i].currN*sinfo[i].currN / m;
		sorbateGlobal[i].avgN_err = sdom * sqrt(sorbateGlobal[i].avgN_sq
			- sorbateGlobal[i].avgN*sorbateGlobal[i].avgN);

		sorbateGlobal[i].percent_wt = factor * sorbateGlobal[i].percent_wt
			+ sinfo[i].percent_wt / m;
		sorbateGlobal[i].percent_wt_sq = factor * sorbateGlobal[i].percent_wt_sq
			+ sinfo[i].percent_wt*sinfo[i].percent_wt / m;
		sorbateGlobal[i].percent_wt_err = sdom * sqrt(sorbateGlobal[i].percent_wt_sq
			- sorbateGlobal[i].percent_wt*sorbateGlobal[i].percent_wt);

		sorbateGlobal[i].percent_wt_me = factor * sorbateGlobal[i].percent_wt_me
			+ sinfo[i].percent_wt_me / m;
		sorbateGlobal[i].percent_wt_me_sq = factor * sorbateGlobal[i].percent_wt_me_sq
			+ sinfo[i].percent_wt_me*sinfo[i].percent_wt_me / m;
		sorbateGlobal[i].percent_wt_me_err = sdom * sqrt(sorbateGlobal[i].percent_wt_me_sq
			- sorbateGlobal[i].percent_wt_me*sorbateGlobal[i].percent_wt_me);

		sorbateGlobal[i].excess_ratio = factor * sorbateGlobal[i].excess_ratio
			+ sinfo[i].excess_ratio / m;
		sorbateGlobal[i].excess_ratio_sq = factor * sorbateGlobal[i].excess_ratio_sq
			+ sinfo[i].excess_ratio*sinfo[i].excess_ratio / m;
		sorbateGlobal[i].excess_ratio_err = sdom * sqrt(sorbateGlobal[i].excess_ratio_sq
			- sorbateGlobal[i].excess_ratio*sorbateGlobal[i].excess_ratio);

		sorbateGlobal[i].pore_density = factor * sorbateGlobal[i].pore_density
			+ sinfo[i].pore_density / m;
		sorbateGlobal[i].pore_density_sq = factor * sorbateGlobal[i].pore_density_sq
			+ sinfo[i].pore_density*sinfo[i].pore_density / m;
		sorbateGlobal[i].pore_density_err = sdom * sqrt(sorbateGlobal[i].pore_density_sq
			- sorbateGlobal[i].pore_density*sorbateGlobal[i].pore_density);

		sorbateGlobal[i].density = factor * sorbateGlobal[i].density
			+ sinfo[i].density / m;
		sorbateGlobal[i].density_sq = factor * sorbateGlobal[i].density_sq
			+ sinfo[i].density*sinfo[i].density / m;
		sorbateGlobal[i].density_err = sdom * sqrt(sorbateGlobal[i].density_sq
			- sorbateGlobal[i].density*sorbateGlobal[i].density);

	}

	// calculate selectivity
	for ( int i=0; i<sorbateCount; i++ ) {
		numerator = sorbateGlobal[i].avgN;
		relative_err = sorbateGlobal[i].avgN_err * sorbateGlobal[i].avgN_err
			/ ( sorbateGlobal[i].avgN * sorbateGlobal[i].avgN );
		denominator = 0;
		for ( int j=0; j<sorbateCount; j++ ) {
			if ( j==i ) 
				continue;
			denominator += sorbateGlobal[j].avgN;
			relative_err += sorbateGlobal[j].avgN_err * sorbateGlobal[j].avgN_err   /   ( sorbateGlobal[j].avgN * sorbateGlobal[j].avgN );
		}
		sorbateGlobal[i].selectivity = numerator/denominator;
		sorbateGlobal[i].selectivity_err =
			sorbateGlobal[i].selectivity * sqrt(relative_err);
	}

	return;
}



void System::clear_avg_nodestats() {

	avg_nodestats->counter = 0;

	avg_observables->boltzmann_factor = 0;
	avg_observables->boltzmann_factor_sq = 0;

	avg_observables->acceptance_rate = 0;
	avg_observables->acceptance_rate_insert = 0;
	avg_observables->acceptance_rate_remove = 0;
	avg_observables->acceptance_rate_displace = 0;
	avg_observables->acceptance_rate_adiabatic = 0;
	avg_observables->acceptance_rate_spinflip = 0;
	avg_observables->acceptance_rate_volume = 0;
	avg_observables->acceptance_rate_ptemp = 0;

	avg_observables->cavity_bias_probability = 0;
	avg_observables->cavity_bias_probability_sq = 0;

	avg_observables->polarization_iterations = 0;
	avg_observables->polarization_iterations_sq = 0;

	return;
}




void System::update_root_nodestats( avg_nodestats_t *avg_nodestats, avg_observables_t *avg_observables) {

	double m      = 0,
	       factor = 0,
	       sdom   = 0;

	m = (double)(++avg_nodestats->counter);
	sdom = 1.0 / sqrt(floor((double)((step+1.0)*size)/(double)(corrtime))-1.0);
	factor = (m - 1.0)/m;

	avg_observables->boltzmann_factor = factor*avg_observables->boltzmann_factor 
		+ avg_nodestats->boltzmann_factor / m;
	avg_observables->boltzmann_factor_sq = factor*avg_observables->boltzmann_factor_sq 
		+ avg_nodestats->boltzmann_factor_sq / m;
	avg_observables->boltzmann_factor_error = sdom*sqrt(avg_observables->boltzmann_factor_sq 
		- avg_observables->boltzmann_factor*avg_observables->boltzmann_factor);

	avg_observables->acceptance_rate = factor*avg_observables->acceptance_rate 
		+ avg_nodestats->acceptance_rate / m;
	avg_observables->acceptance_rate_insert = factor*avg_observables->acceptance_rate_insert 
		+ avg_nodestats->acceptance_rate_insert / m;
	avg_observables->acceptance_rate_remove = factor*avg_observables->acceptance_rate_remove 
		+ avg_nodestats->acceptance_rate_remove / m;
	avg_observables->acceptance_rate_displace = factor*avg_observables->acceptance_rate_displace 
		+ avg_nodestats->acceptance_rate_displace / m;
	avg_observables->acceptance_rate_adiabatic = factor*avg_observables->acceptance_rate_adiabatic 
		+ avg_nodestats->acceptance_rate_adiabatic / m;
	avg_observables->acceptance_rate_spinflip = factor*avg_observables->acceptance_rate_spinflip 
		+ avg_nodestats->acceptance_rate_spinflip / m;
	avg_observables->acceptance_rate_volume = factor*avg_observables->acceptance_rate_volume 
		+ avg_nodestats->acceptance_rate_volume / m;
	avg_observables->acceptance_rate_ptemp = factor*avg_observables->acceptance_rate_ptemp 
		+ avg_nodestats->acceptance_rate_ptemp / m;

	avg_observables->cavity_bias_probability = factor*avg_observables->cavity_bias_probability 
		+ avg_nodestats->cavity_bias_probability / m;
	avg_observables->cavity_bias_probability_sq = factor*avg_observables->cavity_bias_probability_sq 
		+ avg_nodestats->cavity_bias_probability_sq / m;
	avg_observables->cavity_bias_probability_error = sdom*sqrt(avg_observables->cavity_bias_probability_sq 
		- avg_observables->cavity_bias_probability*avg_observables->cavity_bias_probability);

	avg_observables->polarization_iterations = factor*avg_observables->polarization_iterations 
		+ avg_nodestats->polarization_iterations / m;
	avg_observables->polarization_iterations_sq = factor*avg_observables->polarization_iterations_sq 
		+ avg_nodestats->polarization_iterations_sq / m;
	avg_observables->polarization_iterations_error = sdom*sqrt(avg_observables->polarization_iterations_sq 
		- avg_observables->polarization_iterations*avg_observables->polarization_iterations);

	return;
}
