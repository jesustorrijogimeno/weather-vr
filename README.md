# WeatherVR



## API Integration

The services in which the API is called are in the Services folder, in which the following files are:
- WWServiceCommons -> It has the generic methods to make GET calls and error handling
- WWeatherService -> It has the methods in which the WWServiceCommons functions are used, the API calls are created and the results are processed. Specifically, the Latitude and Longitude are first obtained from the name of the city, and then with that data the meteorological data is obtained in a second call.
- WServiceConstants -> Constants for the use of services (API keys, url's...)

The call to obtain weather data is made when you click on the city through the UI. The buttons have a delegate to which the main UI subscribes, which is the one in charge of making the call. It can be seen in UI/WCitiesSelectorBase and UI/WButtonCityBase.
After receiving the data, all objects that implement the IWUpdateEnvironment interface are called, which in this case is only the Actor/WSkySystemBase.

## Sky and weather system

The daytime system and the weather system are in the same blueprint since they affect the same components. The blueprint is called BP_DynamicSky.
En este blueprint he expuesto varias variables para poder probar en editor diferentes entornos y cambiar configuraciones facilmente.
Since it is difficult for all the possible weather configurations to appear in the 10 cities of the UI, these can be easily tested with the following parameters:

- Settings
    - Time of Day -> To switch between different times of the day.
    - Sunrise -> Sunrise time setting
    - Sunset -> Dusk time setting
    - Weather Condition -> This is the most important since with this you can change between the different weather configurations. Supported conditions are Clear, Rain, Thunderstom, Drizzle, Snow and Clouds.

There is also the Night Settings and Weather section in which you can change parameters for the night or weather, but these should not be changed unless you want to adjust the weather settings already created.

There are certain limitations, such as if the atmospheric condition is Rain, Thunderstorm or Snow, even if it is night, everything is seen the same as if it were day.
To create this, I have set up a sky sphere with its material (Materials/Sky/M_Sky_Sphere) in which I have added clouds and the moon.
For snow and rain I have created particle systems using Niagara but I have limited it to only spawning where the camera is, so the performance does not suffer much.

## VR
For VR I used the VRTemplate, but I had to add functions to VRPawn to be able to simulate clicking on the UI buttons.