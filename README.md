#Instructions to use it without Pacpus

Install PCL and compile & run any of the test_*.cpp file

#Instructions to use it with Pacpus

##Compile & Install Pacpus
https://devel.hds.utc.fr/svn/pacpusframework/
https://devel.hds.utc.fr/svn/pacpusbase/
https://devel.hds.utc.fr/svn/pacpussensors/

See instructions on the wiki because things are moving at the moment

##Compile && PacpusSensors

	export PACPUS_ROOT="/opt/pacpus/0.0.1"
	cd pacpus/pacpussensors/trunk/build/
	./build_linux.sh

Add files in this repository to get the last working version of PacpusSensors with Velodyne

##Data player

	PATH=$PATH:/opt/pacpus/0.0.1/bin
	cd pacpus/
	DBITEPlayer_d xml/conf.xml

##Data viewer

	PATH=$PATH:/opt/pacpus/0.0.1/bin
	cd pacpus/
	PacpusSensor_d xml/compute.xml
