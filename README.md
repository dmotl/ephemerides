# Ephemerides of variable stars

Interactive computer program for computing ephemerides of eclipsing binary stars

## Description

Ephemerides is a computer program which computes times of minima of eclipsing binary stars. The
data of variable stars are read from several catalogue files. It is intended to be used off-line, no internet 
connection is required at run-time. The current version works in the MS Windows 2000 and newer. 
It is intended for visual, CCD and PE observers.

The graphical user interface is very simple and intuitive. It can be run in the two operation modes: 
the computation ephemerides for one specific night or the computation of ephemerides for a particular 
variable star and a season. It is possible to print the table of minima on a connected printer or save 
it to an ASCII, HTML or CSV file.

It is possible to build and use a custom catalogue file of your own variables.

## Licence

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License, Version 2, as published 
by the Free Software Foundation.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
FITNESS FOR A PARTICULAR PURPOSE.  

See the COPYING file for more details.

## Installation

### What do I need?

A computer with MS Windows 2000, XP, Vista or Windows 7, 8 or 10. There are no special 
requirements on hardware. Program takes about 2.8 MB on your hard disk and a few megabytes of RAM.

### Where can I download it?

The build/win32 folder in this repository contains binary installation packages.
The packages also comes with the electronic help in english and czech language.

GitHub project: <a href="https://github.com/dmotl/ephemerides">https://github.com/dmotl/ephemerides</a>

### What catalogs of variable stars does the software include?

Current installation package contains following catalogue files:

 * BRNO - B.R.N.O. project on eclipsing binary observing, see <a href="http://var.astro.cz/brno/">http://var.astro.cz/brno/</a>, valid to 29. July 2018
 
 * BRKA 2005 - selection of stars from the B.R.N.O. project, now obsolete
 
 * Prosper - project, which is concerned on new or neglected eclipsing binary stars, valid to 10. Aug 2006
 
The BRNO catalog file was compiled using the information from the <a href="http://var.astro.cz/ocgate/">O-C gate</a>

Because the original source does not contain some useful information, the GCVS catalog and its supplements was used to fill 
in the variability type, eclipse duration (D) and GSC identification.

### Can I use other (my own) catalogs?

Yes, you can use the software to predict minima of any variables star, you need to create a catalog file in specified format.
Refer to the user guide for format description.

### How shall I install it?

Download the binary installation package (see above). Save it to your disk 
and start. The installation package contains simple wizard, which will guide you through 
the rest of the installation. It doesn't require rebooting the computer.

### Where can I get help?

The electronic help is included in the installation. You can open it from
the 'Start' menu or in the application main window by clicking on the button with the question 
mark on the toolbar. When everything has failed, please contact the project administrator.

### How to uninstall it?

Run 'uninstall' program in the installation directory or open the Control panel
and use the 'Install or remove program' tool.

### Is the source code also available?

Yes, the source code is available on GitHub. It's been written in Borland Delphi 7.

Git repository: <a href="https://github.com/dmotl/ephemerides.git">https://github.com/dmotl/ephemerides.git</a>


## Author

David Motl, dmotl (at) volny (dot) cz


## Bug reports

Send bug reports, comments, suggestions to the mailbox: dmotl (at) volny (dot) cz


## History

See the CHANGELOG file


## References

 * Pokorný Z.: Astronomické algoritmy pro kalkulátory
 * Zejda, M. a kol.: Pozorování promìnných hvìzd I., Brno 1994
 * Zejda M. a kol.: Katalog BRKA 2005, <a href="http://var.astro.cz/brno/brka.html">http://var.astro.cz/brno/brka.html</a>
 * NASA Learning Technologies, World Wind 1.2e, <a href="http://worldwind.arc.nasa.gov/">http://worldwind.arc.nasa.gov/</a> - the image of the Earth
 * SOHO (ESA &amp; NASA), <a href="http://sohowww.nascom.nasa.gov/">http://sohowww.nascom.nasa.gov/</a> - the image of the Sun
 * Yale Bright Star Catalog - star catalogue on sky chart tool
 * Nullsoft Scriptable Installation System, the instalation compiler, by Nullsoft, <a href="http://nsis.sf.net">http://nsis.sf.net</a>
 * O-C gateway, <a href="http://var.astro.cz/ocgate/">http://var.astro.cz/ocgate/</a>
 * Samus N.N., Durlevich O.V., Kazarovets E V., Kireeva N.N., Pastukhova E.N., Zharova A.V., et al., General Catalogue of Variable Stars (Samus+ 2007-2012), <a href="http://cdsarc.u-strasbg.fr/viz-bin/Cat?cat=B%2Fgcvs&">VizieR On-line Data Catalog: B/gcvs</a>
 

## My other projects

### C-Munipack

The C-Munipack is the software package, which offers the complete solution for reduction of images 
carried out by CCD camera, intended on a observation of variable stars. Each step of reduction process can be run from 
the command line or via simple and intuitive graphical user interface.		   

The software free for use, open-source, licenced under GPL GNU.

Home page: http://c-munipack.sourceforge.net/

