# Mesh generering #

Mesh generering bör inte använda DirectX-primitiver då dessa saknar texturkoordinater. Istället bör egen meshgenerering implementeras.

# Modellhierarki #

Hierarkin för modeller bör tänkas igenom. För närvarande fungerar inte clone-operatorn för modeller då varje modell renderas inviduellt oberoende av eventuell ägande förälder.

# No op #

En no op-operator kan faktiskt vara rätt najs att ha när man använder sig av många operatorer.