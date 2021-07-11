<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.5" tiledversion="1.6.0" name="Masters_Test" tilewidth="256" tileheight="256" tilecount="3" columns="0">
 <grid orientation="orthogonal" width="1" height="1"/>
 <tile id="0" type="white_walkable">
  <properties>
   <property name="walkable" type="bool" value="true"/>
  </properties>
  <image width="256" height="256" source="walkable_square.png"/>
 </tile>
 <tile id="1" type="deadly">
  <properties>
   <property name="deadly" type="bool" value="true"/>
   <property name="walkable" type="bool" value="true"/>
  </properties>
  <image width="256" height="256" source="deadly_square.png"/>
 </tile>
 <tile id="2">
  <properties>
   <property name="start" type="bool" value="true"/>
  </properties>
  <image width="256" height="256" source="start_square.png"/>
 </tile>
</tileset>
