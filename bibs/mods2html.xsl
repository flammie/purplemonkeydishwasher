<?xml version="1.0"?>

<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xpath-default-namespace="http://www.loc.gov/mods/v3">

    <xsl:output method="html" version="5.0"/>

    <xsl:template match="modsCollection">
        <html>
            <head>
                <meta charsent="utf-8"/>
                <title>
                    Flammie’s bibliography: generated from pirinen.bib
                </title>
                <meta name="description">
                    Flammie A Pirinen’s academic bibliography is listing of
                    academic articles, books and other content for purposes
                    of citations.
                </meta>
            </head>
            <body>
                <h1>Flammie’s academic bibliography</h1>
                <p style="font-variant: italic">
                    This listing has been generated automatically from the bib
                    bibliography data. It is intended for a quick overview, to
                    actually cite the publications here, use <a
                    href="pirinen.bib">pirinen.bib</a> or <a
                    href="pirinen.enw">pirinen.enw</a> for example.
                </p>
                <table>
                    <thead>
                        <tr>
                            <th>Title</th>
                            <th>Authors (year)</th>
                            <th>Other informations</th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:apply-templates select="mods"/>
                    </tbody>
                </table>
                <hr title="beginning of metadata"/>
                <p>Listing generated with
                <a href="https://github.com/flammie/purplemonkeydishwasher/">
                    mods2html.xsl</a>.
                </p>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="mods">
        <tr>
            <td><xsl:apply-templates select="titleInfo"/></td>
            <td>
                <xsl:for-each select="name[@type='personal']">
                    <xsl:apply-templates select="."/>
                    <xsl:if test="position() != last()">; </xsl:if>
                </xsl:for-each>
                (<xsl:value-of select="originInfo/dateIssued"/>)
            </td>
            <td>
                <xsl:for-each select="genre">
                    <xsl:apply-templates select="."/>
                    <xsl:if test="position() != last()">; </xsl:if>
                </xsl:for-each>
                <xsl:text> </xsl:text>
                <xsl:apply-templates select="relatedItem"/>
                <xsl:text> </xsl:text>
                <xsl:apply-templates select="part"/>
                <xsl:text> </xsl:text>
                <xsl:apply-templates select="note"/>
            </td>
        </tr>
    </xsl:template>

    <xsl:template match="titleInfo">
        <xsl:apply-templates select="title"/>
    </xsl:template>

    <xsl:template match="name">
        <xsl:apply-templates select="namePart[@type='family']"/>,
        <xsl:for-each select="namePart[@type='given']">
            <xsl:apply-templates select="."/>
            <xsl:text> </xsl:text>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="part">
        (<xsl:apply-templates select="date"/>)
        <xsl:apply-templates select="extent"/>
    </xsl:template>

    <xsl:template match="extent">
        <xsl:apply-templates select="@unit"/>:
        <xsl:apply-templates select="start"/>–<xsl:apply-templates select="end"/>
    </xsl:template>

    <xsl:template match="note">
        (<xsl:value-of select="."/>)
    </xsl:template>
</xsl:stylesheet>
