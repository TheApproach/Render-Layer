# Support Files

Any files supporting your runtime but not directly part of your project or Approach's class system should ideally go here.
This includes 3rd party libraries, pattern files, metadata documents. Generally if your project is going to LOAD something from disk and that something should be package with your project, then it probably belongs in /support. Likely you will customize support structure further.


- /support/lib		Location of file-system dependencies for your project runtime. Separates permissions from executable paths. Writeable, readable only. 

- - /extension		Production grade packages with the highest certification possible in scale and security
- - /community		Community maintained, mixed-model packages which are certified as compliant in scale and security
- - /vendor		Actively maintained, for-profit packages which are certified as compliant in scale and security
- - /wild		Default location for packages published to the Approach Network via blockchain signing


- /support/pattern	Approach pattern files for your project

- - /[customized]	Depends on your project needs. Default structure TBD
- - /editor		Contains patterns which provide UI to edit specific Components
- - /props		Prop library which may be used by UI services whether client-side or server-side


- /support/binding	Mappings from one type to another created using one of Approach's Web GUI tools. 
- - /tokens		For instance from product table(s) to tokens in a product view.
- - /settings		For instance from product table(s) to various form handling props capable of setting such values
- - /import		For instance from some API to your internal data storage
- - /export		From any Approach layer to any format

- /support/test		Contains unit, functional, acceptance, etc.. tests. 