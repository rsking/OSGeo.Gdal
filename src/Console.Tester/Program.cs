// -----------------------------------------------------------------------
// <copyright file="Program.cs" company="GeomaticTechnologies">
// Copyright (c) 2013, GeomaticTechnologies. All rights reserved.
// </copyright>
// -----------------------------------------------------------------------

namespace Console.Tester
{
    using System;

    /// <summary>
    /// The testing program.
    /// </summary>
    internal class Program
    {
        /// <summary>
        /// Entry point for the program.
        /// </summary>
        private static void Main()
        {
            using (var datasource = OSGeo.Ogr.DataSource.Open("ogrtest_utf.sqlite"))
            {
                Console.WriteLine(datasource.Name);
                foreach (var layer in datasource.Layers)
                {
                    Console.WriteLine(layer.Name);

                    var definition = layer.Definition;
                    foreach (var field in layer.Definition.Fields)
                    {
                       Console.WriteLine(field.Name);
                    }

                    foreach (var feature in layer.Features)
                    {
                        // output the values
                        var fieldString = feature.GetString(21);
                        var values = new object[feature.FieldCount];
                        var valueCount = feature.GetValues(values);

                        foreach (var value in values)
                        {
                            Console.WriteLine(value);
                        }

                        if (feature.Geometry == null)
                        {
                            continue;
                        }

                        var geometry = feature.Geometry;

                        var wkt = geometry.ToString();
                        var wkb = geometry.ToBinary();
                        Console.WriteLine("JSON {0}", geometry.ToString(OSGeo.Ogr.GeometryTextFormat.Json));
                        Console.WriteLine("GML {0}", geometry.ToString(OSGeo.Ogr.GeometryTextFormat.Gml));
                        Console.WriteLine("KML {0}", geometry.ToString(OSGeo.Ogr.GeometryTextFormat.Kml));

                        Console.WriteLine("WKT {0}", OSGeo.Ogr.Geometry.FromText(wkt));
                        Console.WriteLine("WKB {0}", OSGeo.Ogr.Geometry.FromWkb(wkb));

                        var spatialReference = geometry.SpatialReference;
                        Console.WriteLine("SR {0}", spatialReference);

                        var surface = geometry as OSGeo.Ogr.Surface;
                        if (surface != null)
                        {
                            Console.WriteLine(surface.Area);
                        }

                        var polygon = geometry as OSGeo.Ogr.Polygon;
                        if (polygon != null)
                        {
                            var outerRing = polygon.Outer;

                            foreach (var point in outerRing)
                            {
                                Console.WriteLine(point.X);
                            }
                        }
                    }
                }

                var driver = datasource.Driver;
                Console.WriteLine(driver.Name);
            }
        }
    }
}
