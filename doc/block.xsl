<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
	<body>
	<title>Shrimp 2.0 : Standard Blocks</title>


	<a name="stblocks"></a>
	<h1>Shrimp 2.0 : Standard Blocks</h1>
	<xsl:for-each select="block/shrimp">
	<xsl:sort select="@name"/>
		  <xsl:variable name="bc" select="@name"/>
		  <h1><a name="{$bc}">
			<xsl:value-of select="@name"/></a></h1>
		    <hr width="100%"> </hr>
		    <table border="1">
		      <tr>
			<th bgcolor="#ff4040">Type</th>
			<td><xsl:value-of select="@type"/></td>
		      </tr>
		      
		      <tr>
			<th bgcolor="#ff4040">Description</th>
			<td><dfn><xsl:value-of select="@description"/></dfn></td>
		      </tr>
		      <tr>
			<th bgcolor="#ff4040">Usage</th>
			<td><dfn><xsl:value-of select="usage"/></dfn></td>
		      </tr>
		    </table>
		  <h3>Input</h3>
		  <table border="1">
		      <tr bgcolor="#80ff80">
			<th>Name</th>
			<th>Description</th>
			<th>Type</th>
			<th>Storage</th>
			<th>Default</th>
		      </tr>
	
		  	<xsl:for-each select="input">
			<tr>
				<td><xsl:value-of select="@name"/></td>
				<td><xsl:value-of select="@description"/></td>
				<td><xsl:value-of select="@type"/></td>
				<td><xsl:value-of select="@storage"/></td>
				<td><xsl:value-of select="@default"/></td>
			</tr>
		
			</xsl:for-each>
		  </table>
		  <h3>Output</h3>
		<table border="1">
		      <tr bgcolor="#8080ff">
			<th>Name</th>
			<th>Description</th>
			<th>Type</th>
		      </tr>
	
		  	<xsl:for-each select="output">
			<tr>
				<td><xsl:value-of select="@name"/></td>
				<td><xsl:value-of select="@description"/></td>
				<td><xsl:value-of select="@type"/></td>
			</tr>
		
			</xsl:for-each>
		  </table>
		  <h3>RSL Code(Xml format) </h3>
		  <td>Include :</td><code>
		  <b><xsl:value-of select="rsl_include"/></b></code>
		  <code>
		  <xsl:call-template name="break">
			<xsl:param name="code" select="shrimp/rsl_code"/>
		  </xsl:call-template>
		  </code>			
	</xsl:for-each>

	</body>
	</html>
</xsl:template>
<xsl:template name="break">
	<xsl:param name="code" select="rsl_code"/>
	<xsl:choose>
		<xsl:when test="contains($code, '&#xa;')">
		      <xsl:value-of select="substring-before($code, '&#xa;')"/>
		      <br/>
		      <xsl:call-template name="break">
			  <xsl:with-param name="code" select="substring-after($code,'&#xa;')"/>
		      </xsl:call-template>
		</xsl:when>
		<xsl:when test="contains($code,';')">
      			<xsl:value-of select="substring-before($code, ';')"/>
      			<xsl:text>; </xsl:text> <br/>
			<xsl:call-template name="break">
      		        	<xsl:with-param name="code" select="substring-after($code,';')"/>
			</xsl:call-template>
   		</xsl:when>
		
	</xsl:choose>
</xsl:template>	

<xsl:template name="text-loop">
  <xsl:param name="max-times" select="1"/>
  <xsl:param name="node" select="1"/>
  <xsl:param name="i" select="1"/>

  <xsl:if test="$i &lt; $max-times">  
	<xsl:variable name="lcletters">abcdefghijklmnopqrstuvwxyz</xsl:variable>
	<xsl:variable name="ucletters">ABCDEFGHIJKLMNOPQRSTUVWXYZ</xsl:variable>
    		<xsl:if test="substring($lcletters,$i,1) = substring($node,1,1) or substring($ucletters,$i,1) = substring($node,1,1) ">
			
			<tr>
			<xsl:variable name="bc" select="@name"/>
			<th><a href="{concat('index.xml#',$bc)}" target ="blocks" ><xsl:value-of select="$node"/></a></th>
			
			</tr>
  		</xsl:if>
    <xsl:call-template name="text-loop">
      <xsl:with-param name="max-times" select="$max-times"/>
      <xsl:with-param name="node" select="$node"/>
      <xsl:with-param name="i" select="$i + 1"/>
    </xsl:call-template>
  </xsl:if>
</xsl:template>
</xsl:stylesheet>


