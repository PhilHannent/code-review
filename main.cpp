#include <QCoreApplication>

#include <QColor>
#include <QPainterPath>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}

//////////////////////////////////////////////////////////////////
/// 1.
//////////////////////////////////////////////////////////////////


QColor getSVGColour(QString sColour)
{
    QColor newcolour;

    if (sColour.contains("rgb"))
    {
        sColour = sColour.replace("rgb", "");
        sColour = sColour.replace("(", "");
        sColour = sColour.replace(")", "");

        if (sColour.contains("%"))
        {
            sColour = sColour.replace("%", "");
            QStringList rgb = sColour.split(",");
            newcolour = QColor(int(rgb[0].toInt() * 2.55),
                               int(rgb[1].toInt() * 2.55),
                               int(rgb[2].toInt() * 2.55));
        }
        else
        {
            QStringList rgb = sColour.split(",");
            newcolour = QColor(int(rgb[0].toInt()),
                               int(rgb[1].toInt()),
                               int(rgb[2].toInt()));
        }
    }
    else
    {
        newcolour = QColor(sColour);
    }

    return newcolour;
}

//////////////////////////////////////////////////////////////////
/// 2.
//////////////////////////////////////////////////////////////////
struct PathData
{
    int maxAngle;
    int checkedElementCount;
};

PathData * get_max_angle_change(QPainterPath p) {

    PathData * d = new PathData();

    if (p.elementCount() == 0)
        return d;

    for (int i = 1; i <= p.elementCount(); i++) {

        if (p.elementAt(i).type == QPainterPath::ElementType::CurveType) {
            throw new std::invalid_argument("cannot parse paths with curves");
        }

        switch (p.elementAt(i).type) {
            case QPainterPath::ElementType::MoveType:
            {
                // do nothing
            }
            case QPainterPath::ElementType::LineType:
            {
                d->checkedElementCount++;
                d->maxAngle = qMax(QLineF(p.elementAt(i - 1).operator QPointF(),
                                          p.elementAt(i).operator QPointF())).angle(),
                                    d->maxAngle);
            }
            default:
            {
                throw new std::invalid_argument("cannot parse paths with curves");
            }
        }
    }

    return d;
}



//////////////////////////////////////////////////////////////////
/// 3.
//////////////////////////////////////////////////////////////////

int Lynx::TextFrame::effectiveLineCount() const
{
    Q_D(const TextFrame);
    if (d->m_document == nullptr)
    {
        return 0;
    }

    int count = 0;

    QTextCursor c(d->m_document.data());
    c.setVisualNavigation(true);
    c.movePosition(QTextCursor::Start);

    bool isNotDone = true;

    while (isNotDone)
    {
        isNotDone = c.movePosition(QTextCursor::Down);
        count++;
    }

    return count;
}
