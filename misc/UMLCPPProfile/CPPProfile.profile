<?xml version="1.0" encoding="utf-8"?>
<profile dslVersion="1.0.0.0" 
       name="CSharpProfile" displayName="C# Profile" 
       xmlns="http://schemas.microsoft.com/UML2.1.2/ProfileDefinition">
  <stereotypes>
    <!-- C++ Class -->
    <stereotype name="class" displayName="C++ class">
      <metaclasses>
        <metaclassMoniker name="/CPPProfile/Microsoft.VisualStudio.Uml.Classes.IClass" />
      </metaclasses>
      <properties>
      </properties>
    </stereotype>

    <!-- C# Enum -->
    <stereotype name="enum" displayName="C++ enum">
      <metaclasses>
        <metaclassMoniker name="/CPPSharpProfile/Microsoft.VisualStudio.Uml.Classes.IEnumeration" />
      </metaclasses>
      <properties>
        <property name="BaseType" displayName="Base Type" defaultValue="int">
          <propertyType>
            <enumerationTypeMoniker name="/CPPharpProfile/EnumBaseType"/>
          </propertyType>
        </property>
      </properties>
    </stereotype>
    
    
  </stereotypes>
  
  <!-- All metaclasses referenced by a stereotype defined in this profile -->
  <metaclasses>
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IClass" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IDependency" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IEnumeration" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IInterface" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IOperation" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IPackage" />
    <metaclass name="Microsoft.VisualStudio.Uml.Classes.IPackageImport" />
  </metaclasses>

  <!-- Property Types referenced by a stereotype property defined in this profile -->
  <propertyTypes>
    <externalType name="System.String" />
    <externalType name="System.Boolean" />
    <enumerationType name="EnumBaseType">
      <enumerationLiterals>
        <enumerationLiteral name="char" displayName="char" />
        <enumerationLiteral name="unsigned char" displayName="unsigned char" />
        <enumerationLiteral name="int" displayName="int" />
        <enumerationLiteral name="unsigned int" displayName="unsigned int" />
        <enumerationLiteral name="long" displayName="long" />
        <enumerationLiteral name="unsigned long" displayName="unsigned long" />
        <enumerationLiteral name="long long" displayName="long long" />
        <enumerationLiteral name="unsigned long long" displayName="unsigned long long" />
        <enumerationLiteral name="short" displayName="short" />
        <enumerationLiteral name="unsigned short" displayName="unsigned short" />
        <enumerationLiteral name="int32_t" displayName="int32_t" />
        <enumerationLiteral name="uint32_t" displayName="uint32_t" />
        <enumerationLiteral name="int16_t" displayName="int16_t" />
        <enumerationLiteral name="uint16_t" displayName="uint16_t" />
        <enumerationLiteral name="int8_t" displayName="int8_t" />
        <enumerationLiteral name="uint8_t" displayName="uint8_t" />
      </enumerationLiterals>
    </enumerationType>
  </propertyTypes>
</profile>