namespace Console.Tester
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    using OSGeo.Ogr;

    class Program
    {
        static void Main(string[] args)
        {
            using (var datasource = DataSource.Open("ogrtest_utf.sqlite"))
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

                        if (feature.Geometry == null)
                        {
                            continue;
                        }

                        var geometry = feature.Geometry;

                        var wkt = geometry.ToString();
                        var wkb = geometry.ToBinary();
                        var json = geometry.ToString(GeometryTextFormat.Json);
                        var gml = geometry.ToString(GeometryTextFormat.Gml);
                        var kml = geometry.ToString(GeometryTextFormat.Kml);
                        //Console.WriteLine(wkt);

                        var fromWkt = Geometry.FromText(wkt);
                        var fromWkb = Geometry.FromWkb(wkb);

                        var spatialReference = geometry.SpatialReference;
                        var reft = spatialReference.ToString();

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
