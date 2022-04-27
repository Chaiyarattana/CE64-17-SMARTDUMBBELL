import 'package:flutter/material.dart';
import '../menu_screen/menu_screen.dart';
import '../menu_screen/add_gesture_screen.dart';
import '../constants.dart';
import 'package:flutter_blue/flutter_blue.dart';
import '../main.dart';
import 'dart:async';
import 'dart:math';

class Home extends StatefulWidget {
  final String title;

  const Home({Key? key, required this.title, required this.device})
      : super(key: key);
  final BluetoothDevice device;
  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
  static const ISSC_PROPRIETARY_SERVICE_UUID =
      "6e400001-b5a3-f393-e0a9-e50e24dcca9e";
//device char for ISSC characteristics
  static const UUIDSTR_ISSC_TRANS_TX = "6e400002-b5a3-f393-e0a9-e50e24dcca9e";
  static const UUIDSTR_ISSC_TRANS_RX = "6e400003-b5a3-f393-e0a9-e50e24dcca9e";
  int _selectedIndex = 0;
  // static const TextStyle optionStyle =
  //     TextStyle(fontSize: 30, fontWeight: FontWeight.bold);
  final List<Widget> _widgetOptions = <Widget>[
    const HomeScreen(),
    const MenuScreen(),
  ];
  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
      _widgetOptions[1] = const MenuScreen();
    });
  }

  late BluetoothCharacteristic characteristicsRead, characteristicsWrite;

  _bluetoothService(BluetoothDevice device) async {
    await device.connect();
    List<BluetoothService> services = await device.discoverServices();
    for (var service in services) {
      if (service.uuid.toString() == ISSC_PROPRIETARY_SERVICE_UUID) {
        for (var characteristics in service.characteristics) {
          if (characteristics.uuid.toString() == UUIDSTR_ISSC_TRANS_TX) {
            characteristicsWrite = characteristics;
          }
          if (characteristics.uuid.toString() == UUIDSTR_ISSC_TRANS_RX) {
            characteristicsRead = characteristics;
          }
        }
      }
    }
    // print({characteristicsRead, characteristicsWrite});
  }

  @override
  Widget build(BuildContext context) {
    _bluetoothService(widget.device);
    return Scaffold(
      appBar: AppBar(
          centerTitle: false,
          title: Text(widget.title),
          actions: <Widget>[
            if (_selectedIndex == 1)
              IconButton(
                icon: const Icon(Icons.add_outlined),
                tooltip: 'Add Gesture',
                onPressed: () async {
                  await characteristicsWrite
                      .write([47], withoutResponse: false);
                  await characteristicsWrite.read();
                  setState(() {
                    _widgetOptions[1] = const AddGestureScreen();
                  });
                },
              )
            else
              Container(),
            StreamBuilder<BluetoothDeviceState>(
              stream: widget.device.state,
              initialData: BluetoothDeviceState.connecting,
              builder: (c, snapshot) {
                VoidCallback? onPressed;
                String text;
                switch (snapshot.data) {
                  case BluetoothDeviceState.connected:
                    onPressed = () => Navigator.of(context).pushReplacement(
                            MaterialPageRoute(builder: (context) {
                          widget.device.disconnect();
                          return const MyApp();
                        }));
                    text = 'DISCONNECT';

                    break;
                  case BluetoothDeviceState.disconnected:
                    onPressed = () => widget.device.connect();
                    text = 'CONNECT';
                    break;
                  default:
                    onPressed = null;
                    text = snapshot.data.toString().substring(21).toUpperCase();
                    break;
                }
                return TextButton(
                    onPressed: onPressed,
                    child: Text(
                      text,
                      style: Theme.of(context)
                          .primaryTextTheme
                          .button
                          ?.copyWith(color: Colors.white),
                    ));
              },
            )
          ]),
      body: Container(
        child: _widgetOptions.elementAt(_selectedIndex),
      ),
      bottomNavigationBar: BottomNavigationBar(
        showSelectedLabels: false,
        showUnselectedLabels: false,
        items: const <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.menu),
            label: 'Menu',
          ),
        ],
        currentIndex: _selectedIndex,
        selectedItemColor: buttonGetStartColor,
        onTap: _onItemTapped,
      ),
    );
  }
}

class HomeScreen extends StatefulWidget {
  const HomeScreen({Key? key}) : super(key: key);

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  @override
  Widget build(BuildContext context) {
    return Container(
      child: Column(
        children: <Widget>[
          //Body Container
          Expanded(
            child: SingleChildScrollView(
              padding: const EdgeInsets.symmetric(horizontal: 30.0),
              child: Column(
                children: <Widget>[
                  Row(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: [
                      Container(
                        margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                        child: Container(
                          width: 150,
                          height: 75,
                          decoration: BoxDecoration(
                            borderRadius: BorderRadius.only(
                              topLeft: Radius.circular(21),
                              topRight: Radius.circular(21),
                              bottomLeft: Radius.circular(21),
                              bottomRight: Radius.circular(21),
                            ),
                            color: Color.fromRGBO(255, 255, 255, 1),
                            border: Border.all(
                              color: Color.fromRGBO(0, 0, 0, 1),
                              width: 2,
                            ),
                          ),
                        ),
                      ),
                    ],
                  ),
                  Container(
                    decoration: BoxDecoration(
                        borderRadius: BorderRadius.only(
                          topLeft: Radius.circular(21),
                          topRight: Radius.circular(21),
                          bottomLeft: Radius.circular(21),
                          bottomRight: Radius.circular(21),
                        ),
                        image: DecorationImage(
                            image: NetworkImage(
                                "https://cdn.discordapp.com/attachments/895866960129179758/968040277321338930/unknown.png"),
                            fit: BoxFit.cover)),
                    margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                    child: Container(
                      width: 500,
                      height: 175,
                    ),
                  ),
                  Column(
                    mainAxisAlignment: MainAxisAlignment.start,
                    children: [
                      Row(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Container(
                              decoration: BoxDecoration(
                                  borderRadius: BorderRadius.only(
                                    topLeft: Radius.circular(21),
                                    topRight: Radius.circular(21),
                                    bottomLeft: Radius.circular(21),
                                    bottomRight: Radius.circular(21),
                                  ),
                                  boxShadow: [
                                    BoxShadow(
                                      color: Colors.grey.withOpacity(0.6),
                                      spreadRadius: 4,
                                      blurRadius: 2,
                                      offset: Offset(0, 1),
                                    ),
                                  ],
                                  image: DecorationImage(
                                      image: NetworkImage(
                                          "https://cdn.discordapp.com/attachments/895866960129179758/968051981233029140/Screenshot_2022-04-25-14-29-22-19.jpg"),
                                      fit: BoxFit.cover)),
                              margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                              child: Container(
                                width: 160,
                                height: 160,
                                child: Align(
                                  alignment: Alignment.bottomCenter,
                                  child: Text(
                                    'ARM',
                                    // maxLines: 10,
                                    textAlign: TextAlign.center,
                                    style: TextStyle(
                                      fontSize: 20,
                                      height: 2,
                                      fontWeight: FontWeight.bold,
                                      backgroundColor: Colors.white,
                                    ),
                                  ),
                                ),
                              ),
                            ),
                            SizedBox(
                              width: 40,
                              height: 40,
                            ),
                            Container(
                              decoration: BoxDecoration(
                                  borderRadius: BorderRadius.only(
                                    topLeft: Radius.circular(21),
                                    topRight: Radius.circular(21),
                                    bottomLeft: Radius.circular(21),
                                    bottomRight: Radius.circular(21),
                                  ),
                                  boxShadow: [
                                    BoxShadow(
                                      color: Colors.grey.withOpacity(0.6),
                                      spreadRadius: 4,
                                      blurRadius: 2,
                                      offset: Offset(0, 1),
                                    ),
                                  ],
                                  image: DecorationImage(
                                      image: NetworkImage(
                                          "https://cdn.discordapp.com/attachments/895866960129179758/968051981497298974/Screenshot_2022-04-25-14-28-30-26.jpg"),
                                      fit: BoxFit.cover)),
                              margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                              child: Container(
                                width: 160,
                                height: 160,
                                child: Align(
                                  alignment: Alignment.bottomCenter,
                                  child: Text(
                                    'CHEST',
                                    maxLines: 10,
                                    textAlign: TextAlign.center,
                                    style: TextStyle(
                                      fontSize: 20,
                                      height: 2,
                                      fontWeight: FontWeight.bold,
                                      backgroundColor: Colors.white,
                                    ),
                                  ),
                                ),
                              ),
                            ),
                          ]),
                      Row(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Container(
                              decoration: BoxDecoration(
                                  borderRadius: BorderRadius.only(
                                    topLeft: Radius.circular(21),
                                    topRight: Radius.circular(21),
                                    bottomLeft: Radius.circular(21),
                                    bottomRight: Radius.circular(21),
                                  ),
                                  boxShadow: [
                                    BoxShadow(
                                      color: Colors.grey.withOpacity(0.6),
                                      spreadRadius: 4,
                                      blurRadius: 2,
                                      offset: Offset(0, 1),
                                    ),
                                  ],
                                  image: DecorationImage(
                                      image: NetworkImage(
                                          "https://cdn.discordapp.com/attachments/895866960129179758/968051982021566495/Screenshot_2022-04-25-14-26-45-09.jpg"),
                                      fit: BoxFit.cover)),
                              margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                              child: Container(
                                width: 160,
                                height: 160,
                                child: Align(
                                  alignment: Alignment.bottomCenter,
                                  child: Text(
                                    'SHOULDER',
                                    // maxLines: 10,
                                    textAlign: TextAlign.center,
                                    style: TextStyle(
                                      fontSize: 20,
                                      height: 2,
                                      fontWeight: FontWeight.bold,
                                      backgroundColor: Colors.white,
                                    ),
                                  ),
                                ),
                              ),
                            ),
                            SizedBox(
                              width: 40,
                              height: 40,
                            ),
                            Container(
                              decoration: BoxDecoration(
                                  borderRadius: BorderRadius.only(
                                    topLeft: Radius.circular(21),
                                    topRight: Radius.circular(21),
                                    bottomLeft: Radius.circular(21),
                                    bottomRight: Radius.circular(21),
                                  ),
                                  boxShadow: [
                                    BoxShadow(
                                      color: Colors.grey.withOpacity(0.6),
                                      spreadRadius: 4,
                                      blurRadius: 2,
                                      offset: Offset(0, 1),
                                    ),
                                  ],
                                  image: DecorationImage(
                                      image: NetworkImage(
                                          "https://cdn.discordapp.com/attachments/895866960129179758/968051981690224670/Screenshot_2022-04-25-14-27-22-17.jpg"),
                                      fit: BoxFit.cover)),
                              margin: EdgeInsets.only(top: 15.0, bottom: 15.0),
                              child: Container(
                                width: 160,
                                height: 160,
                                child: Align(
                                  alignment: Alignment.bottomCenter,
                                  child: Text(
                                    'BACK',
                                    // maxLines: 10,
                                    textAlign: TextAlign.center,
                                    style: TextStyle(
                                      fontSize: 20,
                                      height: 2,
                                      fontWeight: FontWeight.bold,
                                      backgroundColor: Colors.white,
                                    ),
                                  ),
                                ),
                              ),
                            ),
                          ])
                    ],
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}
