 #Makefile for HAQ
#Created by Murray Christopherson. Updated April 2011

TOP=..
DEPLIB=$(TOP)/deplib
ARCHI=$(DEPLIB)/Archives

#######################################################################################################################################
#Advanced Users Only
#Below is the script to compile the program. Should work, assuming the macros are specified correctly. Otherwise, edit below this line.
#######################################################################################################################################

.PHONY: all compile-deplib clean

all: compile-deplib

KDCHART=kd_chart-2.4.1-source
QSLOG=QsLog
TINYXML=tinyxml_2_6_1
compile-deplib: $(ARCHI)/$(KDCHART).tar.bz2 $(ARCHI)/$(QSLOG).zip $(ARCHI)/$(TINYXML).tar.gz

	# Compile KD Chart
	cd $(ARCHI) && tar -jxvf $(KDCHART).tar.bz2
	cd $(ARCHI)/$(KDCHART) && ./configure.sh -static -prefix $(PWD)/KDChart && make && make install && make clean

	# Get QsLog
	cd $(ARCHI) && unzip $(QSLOG).zip -d ../QsLog
	rm QsLog/log_example.pro QsLog/main.cpp QsLog/QsLog.pri
	
	# Get TinyXML
	cd $(ARCHI) && tar -zxvf $(TINYXML).tar.gz
	cp -r $(ARCHI)/tinyxml TinyXML
	
clean:
	rm -rf $(ARCHI)/$(KDCHART)
	rm -rf $(ARCHI)/tinyxml
	rm -rf $(DEPLIB)/KDChart
	rm -rf $(DEPLIB)/QsLog
	rm -rf $(DEPLIB)/TinyXML